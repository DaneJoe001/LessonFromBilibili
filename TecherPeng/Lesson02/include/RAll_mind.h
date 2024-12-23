#pragma once

#include <string>
#include <memory>

void func03();

//C++思想:RAll (Resource Acquisdition Is Initialization)
//获取即初始化，释放即销毁资源
//RAll:异常安全(exception-safe)
//C++标准保证当异常发生时，会调用已创建对象的析构函数，因此C++没有（也不需要）finally语句
void check_exception();

class Person
{
public:
    //需不需要自定义析构函数需要考虑类成员是否安全；
    //一般情况：资源管理和数据结构；
    Person();
    //对于单个参数的构造函数
    //使用explicit关闭默认转换
    explicit Person(int weight);

    //C++规定，除智能指针外所有的拷贝都是深拷贝

    Person(const Person&) = default;
    //拷贝构造函数

    Person(Person&&) = default;
    //移动构造函数，C++11标准

    Person& operator=(const Person&) = delete;
    //拷贝赋值函数，支持链式调用

    Person& operator=(Person&&) = default;
    //移动赋值函数，C++11标准

    //对于多参的构造函数
    //体现在括号表达式的赋值上
    //如果不加explicit
    //返回Person的函数，其返回值就可以用{"Jodge",40}
    //C++可以使用{参数列表}直接返回一个struct类
    explicit Person(std::string name, int weight);

    //当定义析构函数时，需要定义或删除拷贝构造或赋值函数
    //以避免原始指针的浅拷贝，避免出现double free
    ~Person() = default;
private:
    std::string m_name;
    //初始化成员为0
    //在基础类型前面加{}都能有效避免随机初始化
    int m_weight{ 0 };
    char m_sex{ 'n' };
};

class CheckClass
{
public:
    CheckClass();
    ~CheckClass();
    void print();
private:
    std::string sentence = "Member in CheckClass!";
};

void check_structure_function();

void func04(CheckClass* ptr);

void func05(std::unique_ptr<CheckClass> ptr);

void func06(std::shared_ptr<CheckClass> ptr);

struct CircleReference
{
    std::shared_ptr<CircleReference>m_child;
    //#define CIRCLE_REFERENCE_EXAMPLE
#ifdef CIRCLE_REFERENCE_EXAMPLE
    std::shared_ptr<CircleReference>m_parent;
#else
    //使用弱引用可以理解为父窗口能拥有子窗口
    //而子窗口并不拥有父窗口
    //弱引用不影响shared_ptr的计数
    //weak_ptr提供了失效检测，更安全
    std::weak_ptr<CircleReference> m_parent;
#endif
    void print();
};

void func07();

void check_smart_pointer();