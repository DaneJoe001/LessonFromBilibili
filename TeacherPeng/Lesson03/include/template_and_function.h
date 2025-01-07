#pragma once
#include <vector>

//typedef与using

typedef int type_int;

using using_int = int;

typedef void* (*type_func_ptr)(void*);

using using_func_ptr = void* (void*);

void check_different_template();

//constexper函数,可以在编译期间就计算完成
//可用于优化性能
inline constexpr bool is_negative(int num)
{
    return num < 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& array)
{
    //__PRETTY_FUNCTION__宏能获取当前函数名称
    os << __PRETTY_FUNCTION__ << std::endl;
    os << "Values in array: {";
    for (int i = 0;i < array.size();i++)
    {
        os << array[i];
        if (i != array.size() - 1)
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

void check_compile_time_contexper_function();

void check_auto_and_reference();

void function_change();