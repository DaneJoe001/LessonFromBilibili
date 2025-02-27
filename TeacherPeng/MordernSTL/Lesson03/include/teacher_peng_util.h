#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#if defined(__GNUC__)||defined(__clang__)
#include <cxxabi.h>
#endif

//小彭老师实现的类型名打印器
//20241224类型打印失败，原因未知
template<class T>
std::string cpp_type_name()
{
    const char* name = typeid(T).name();
#if defined(__GNUC__)||defined(__clang__)
    int status;
    char* p = abi::__cxa_demangle(name, 0, 0, &status);
    std::string s = p;
    std::free(p);
#else
    std::string s = name;
#endif
    if (std::is_const_v<std::remove_reference<T>>)
    {
        s += " const";
    }
    if (std::is_volatile_v<std::remove_reference<T>>)
    {
        s += " volatile";
    }
    if (std::is_lvalue_reference_v<T>)
    {
        s += " &";
    }
    if (std::is_rvalue_reference_v<T>)
    {
        s += " &&";
    }
    return s;
}