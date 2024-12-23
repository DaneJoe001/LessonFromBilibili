#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <RAll_mind.h>

void func03()
{
    std::ofstream fout("test.txt");
    fout << "On sick\n";
    throw std::runtime_error("Broke");
    fout << "Called JavaBean\n";
}

void check_exception()
{
    try
    {
        func03();
    }
    catch (std::exception const& e)
    {
        std::cout << "Catched exception: " << e.what() << std::endl;
    }
}

//对于无参的构造函数
//不使用参数列表的情况下会多一次赋值的损耗
//第一次初始化为空，第二次赋值传入数值
//参数化列表则一步到位
//对于常量成员，必须在构造函数进行初始化
Person::Person() :m_name("peppa"), m_weight(70) {}

Person::Person(int weight) :m_weight(weight) {}

Person::Person(std::string name, int weight) :m_name(name), m_weight(weight) {}

CheckClass::CheckClass()
{
    std::cout << "Malloced!" << std::endl;
}

CheckClass::~CheckClass()
{
    std::cout << "Dismalloced!" << std::endl;
}

void check_structure_function()
{
    //使用{}和()调用构造函数的区别
    //()是强制转换,{}是非强制转换
    //使用{}会使语义更明确
    //Google指出不要用()调用构造函数
    Person person01("Peppa", 70);
    Person person02{ "Jordge", 50 };
    //加了explicit会使下面这种方式失效
    //Person person02 = { "Jordge", 50 };
    //需要类型转换时使用 
    //static_cast<int>(3.14f)而不是int(3.14f)
    //reinterpret_cast<void*>(0xb8000)而不是(void*)0xb8000
    //C++11标准中,当没有提供构造函数时
    //C++11默认提供了一个含有所有成员的构造函数(要按顺序)
    //即使没有提供多参数的构造函数
    //使用{}会依次赋值给对象成员变量
    //Person person03{ "Jack",67,'m' };

    //调用拷贝构造函数
    Person person04 = person02;
    Person person05(person04);
}

void CheckClass::print()
{
    std::cout << sentence << std::endl;
}

void func04(CheckClass* ptr)
{
    ptr->print();
}

std::vector<std::unique_ptr<CheckClass>>obj_list_01;

std::vector<std::shared_ptr<CheckClass>>obj_list_02;

void func05(std::unique_ptr<CheckClass> ptr)
{
    obj_list_01.push_back(std::move(ptr));
}

void func06(std::shared_ptr<CheckClass> ptr)
{
    obj_list_02.push_back(ptr);
}

void func07()
{
#ifndef CIRCLE_REFERENCE_EXAMPLE
    auto parent = std::make_shared<CircleReference>();
    auto child = std::make_shared<CircleReference>();
    parent->m_child = child;
    child->m_parent = parent;
    //由于互相引用的存在导致无法正常释放
    //当child的m_aprent成员为弱引用时，parent会被释放
    parent = nullptr;
    child = nullptr;
#endif
    std::shared_ptr<CheckClass>ptr = std::make_shared<CheckClass>();
    std::weak_ptr<CheckClass>weak = ptr;
    //转移控制权
    obj_list_02.push_back(std::move(ptr));
    std::cout << "Before destructing" << std::endl;
    //当shared_pointer失效时expired()返回false;
    if (weak.expired())
    {
        std::cerr << "Error:Invalid weak_pointer!" << std::endl;
    }
    else
    {
        //有需要的情况下，使用lock会获取强引用
        //当shared_pointer失效时会返回nullptr
        weak.lock()->print();
    }
    std::cout << "After destructing" << std::endl;
    obj_list_02.clear();
    if (weak.expired())
    {
        std::cerr << "Error:Invalid weak_pointer!" << std::endl;
    }
    else
    {
        weak.lock()->print();
    }
}

void CircleReference::print()
{
    std::cout << "Shared pointer is still alive!" << std::endl;
}

void check_smart_pointer()
{

    std::unique_ptr<CheckClass> ptr01 = std::make_unique<CheckClass>();
    //#define EARLIER_RELEASE
#ifdef EARLIER_RELEASE
    std::cout << "Dismalloced in progress!" << std::endl;
    ptr = nullptr;
    return;
#endif
    //unique_ptr不能进行拷贝构造；
    //及不能作为函数参数使用;
    //需要作为函数参数的情况下
    //使用get()方法获取原始指针进行操作
    //使用原始指针的函数得确保不需要资源的所有权
    //使用原始指针需要确保资源未被释放
    func04(ptr01.get());

    //移交所有权
    func05(std::move(ptr01));
    if (ptr01.get() == nullptr)
    {
        std::cout << "NULL when moved!" << std::endl;
    }
    //初始化时计数器置为1
    std::shared_ptr<CheckClass>ptr02 = std::make_shared<CheckClass>();
    //每一次拷贝构造都会使计数器加1
    //当每一次调用析构时，计数器都会减1
    //当计数器为0时，对象才会被销毁
    func06(ptr02);
    func06(ptr02);
    std::cout << "The counter of shared pointer before clearing: " << ptr02.use_count() << std::endl;
    obj_list_02.clear();
    if (ptr02.get() != NULL)
    {
        std::cout << "Exisit after cleared!" << std::endl;
    }
    std::cout << "The counter of shared pointer after clearing: " << ptr02.use_count() << std::endl;
    std::cout << "The end of unit test!" << std::endl;

    //对于使用shared_pointer可能会导致循环引用;
    func07();
    //关于智能指针作为类的成员变量得考虑对象的所有权
    //unique_ptr与原始指针是一对
    //shared_ptr与weak_ptr是一对
    //建议使用shared_ptr于weak_ptr的组合

    return;
}
