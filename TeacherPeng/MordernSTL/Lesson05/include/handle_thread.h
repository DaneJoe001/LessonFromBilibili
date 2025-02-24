#pragma once

#include <vector>
//vector不是多线程安全容器
//多线程访问会造成数据竞争
#include <thread>

class ThreadPool
{
public:
    //在析构函数中销毁线程
    ~ThreadPool();
    void push_back(std::thread thread);
private:
    std::vector<std::thread>m_pool;

};

void handle_thread();

void thread_protect();

#ifdef DEADLOCK
void deadlock_example();
#endif

void try_multi_safety_vector();

void thread_with_conditional_variable();

void try_multi_thread_queue();