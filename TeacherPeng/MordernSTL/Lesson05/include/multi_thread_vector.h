#pragma once

#include <thread>
#include <vector>
#include <shared_mutex>
#include <memory>
#include <mutex>
#define ACCESS_MODE
//#define SHARED_MUTEX
//定义线程安全的vector容器
class MultiThreadVector
{
public:
#ifndef ACCESS_MODE
    void push_back(int value);
    std::size_t size() const;
#else
    //访问者模式，将数据操作和数据分离
    //即向外部提供访问者接口对数据进行操作
    //在数据访问层面可以在构造函数初始化锁，析构函数初始化锁
    //避免了每次在函数内部都要管理锁的麻烦
    //常用于设计GPU容器
    class Accessor
    {
    public:
        Accessor(MultiThreadVector& that);
        void push_back(int value);
        std::size_t size() const;
    private:
        MultiThreadVector& m_that;
        std::unique_lock<std::mutex> m_guard;
    };
    Accessor accessor();
#endif

private:
    std::vector<int> m_array;

#ifndef SHARED_MUTEX
    //size()是const函数，mutex::lock()非const
    //不添加mutable会报错
    //故逻辑上const而部分成员非const添加mutable
    mutable std::mutex m_mutex;
#else
    //读写锁
    mutable std::shared_mutex m_mutex;
#endif



};