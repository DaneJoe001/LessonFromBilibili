#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <exception>

#include <std_container.h>

//迭代器模式
template<class Ptr>
void print(const Ptr begin, const  Ptr end)
{
    for (Ptr it = begin;it != end;it++)
    {
        auto value = *it;
        std::cout << value << '\t';
    }
    std::cout << std::endl;
    //对于链表等存储不连续的类型，可以重载对应的运算符
    //使指针指向下一个节点
}

template<class T>
void print_size(const std::vector<T>array)
{
    std::cout << array.size() << std::endl;
}

//STL五大件
//容器、迭代器、指针、分配器、算法

void check_container()
{
    std::vector<int, std::allocator<int>>array00 = { 1,2,3,4,5,7 };
    std::vector<int> array = { 1,2,3,4,5,7 };
    // auto n = std::count_if(array.begin(), array.end(), std::bind2nd(std::less<int>(), 4));
    // std::cout << n << std::endl;
}

void build_container()
{
    //vector会默认初始化为0
    std::vector<int>array01(5);
    array01[0] = 125;
    //[]运算符不会检查越界,异常访问可能会导致崩溃失败
    array01.at(2) = 251;
    //at()越界会抛出异常
    print_size(array01);
    try
    {
        std::cout << array01.at(5) << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Invalid index!" << '\n';
    }
    //std::vector<int> array02(std::initializer_list<int>list);
    std::cout << "Skip error!" << std::endl;
    //resize()可以扩大也可以缩小
    //resize的优化策略，会扩容1.5到2倍(即不一定按所给参数来)
    array01.resize(8);
    array01.resize(5);
    //clear()可以清空容器元素
    //array01.clear();
    //clear也不会释放内存
    array01.push_back(12);
    array01.pop_back();
    //访问首尾元素
    array01.back();
    array01.front();
    //获取首元素地址
    //传引用或指针可以避免拷贝
    //当resize()更大空间时，会导致之前data()的指针失效
    //当resize()减小空间时，只会修改数组长度，
    //当容器析构时，多余的空间才会一起被释放
    //调用resize()会默认初始化
    //调用reserve()只会new不会初始化
    //由于new需要时间
    //可以使用reserve()预留一定容量
    //reserve()也会导致data()失效
    //reserve只会扩容，传递一个小的参数，不会缩容
    //resize()再扩容会减少一定性能损耗
    int* ptr = array01.data();
    //获取容器的实质容量
    array01.capacity();
    //C++11新增函数
    //shrink_to_fit()用于释放多余容量，减少内存消耗
    //shrink_to_fit()会重新分配一段更小的内存
    //shrink_to_fit()也会导致指针和迭代器失效
    array01.shrink_to_fit();
    //迭代器模式：指针加容器长度
    //尾指针的位置是容器末尾，不可访问
    print(array01.data(), array01.data() + array01.size());
    array01.reserve(20);
    //迭代器可进行切片
    std::vector<int>::iterator begin = array01.begin();
    std::vector<int>::iterator end = array01.end();
    print(begin + 1, end - 1);
    //使用迭代器进行插入
    array01.insert(begin + 3, 233);
    //insert可以重复插入
    array01.insert(begin + 4, 2, 123);
    //C++11insert()可以插入一个列表
    //初始化化列表的类型实质为std::initializer_list<int>
    //不能直接接受另一个容器作为参数
    array01.insert(begin + 2, { 12,23,34,45,56 });
    std::vector<int>array02 = { 1,2,3,4,5 };
    //insert()可以使用迭代器插入另一种容器元素
    array01.insert(array01.begin(), array02.begin(), array02.end());
    //插入数据后迭代器会失效
    begin = array01.begin();
    end = array01.end();
    //C++11
    //当数据源为C数组时可以使用std::begin()和std::end()
    //当对象为具有begin()end()时，会自动调用对应函数
    //C数组时，则替换为首地址和末尾地址
    int C_array[] = { 5,4,3,2,1 };
    array01.insert(array01.begin(), std::begin(C_array), std::end(C_array));
    //使用assign()函数可以进行覆盖操作,不会重新分配内存
    //assign的重载与insert基本类似
    array01.assign(std::begin(C_array), std::end(C_array));
    //vector也可以使用类似的构造函数初始化，会重新分配内存
    //array01 = std::vector<int>(begin, end);

    //erase()函数可以擦除迭代器指向的元素
    //erase()删除后会移动pos后面的元素，故复杂度O(n)
    array01.erase(array01.begin());
    //erase()还可以接受一个迭代器区间，删除指定片段的元素
    print(begin, end);


}