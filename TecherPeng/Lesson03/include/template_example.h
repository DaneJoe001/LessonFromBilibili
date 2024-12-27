#pragma once

#include <iostream>
#include <string>
#include <vector>

//模板不建议分离实现
//模板可以指定默认参数类型
//避免参数中缺少模板类型参数导致编译器无法推断
template<typename T = int>
T func01()
{
    return 1024;
}

//模板可以使用整数类型包括enum作为参数
//模板参数不支持浮点、指针等其他及自定义类型
//当有默认值时，可只用部分参数
//N作为编译期常量传入，对于不同的N会单独生成代码，从而单独优化
//模板元编程由此有益于高性能编程
//但过多使用模板会影响编译速度及生成文件大小
//使用模板参数可以优化性能
template<int N = 4, typename T>
void show_times(T msg)
{
    for (int i = 0;i < N;i++)
    {
        std::cout << "msg: " << msg << std::endl;
    }
}

template<typename T>
//template<class T>与typename完全等价
T twice(T value)
{
    return 2 * value;
}

//特化的重载，会和已有的模板相互重载
template<>
std::string twice(std::string str)
{
    return str + str;
}

//参数部分特化
template<typename T>
T sum(std::vector<T> const& array)
{
    T result = 0;
    for (int i = 0;i < array.size();i++)
    {
        result += array[i];
    }
    return result;
}

template<bool debug>
int sumto(int num)
{
    int result = 0;
    for (int i = 1;i <= num;i++)
    {
        result += i;
        //使用if constexper保证是编译期确定的分支
        //编译期常量限制在于不能通过变量表达式确定
        if constexpr (debug)
        {
            std::cout << i << "-th:" << result << std::endl;
        }
    }
    return result;
}

template<class T1, class T2>
auto add(std::vector<T1> const& array01, std::vector<T2>const& array02)
{
    using T0 = decltype(T1{} + T2{});
    std::vector<T0> result;
    for (size_t i = 0; i < std::min(array01.size(), array02.size());i++)
    {
        result.push_back(array01[i] + array02[i]);
    }
    return result;
}