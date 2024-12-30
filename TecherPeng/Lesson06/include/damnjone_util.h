#pragma once

#include <string>

//可用于打印日志的宏
//__FILE__用于打印整个文件的路径
//__LINE__用于打印当前行号
//__func__用于打印函数名
//__PRETTY_FUNCTION__用于打印函数名，包括返回值和参数
//__PRETTY_FUNCTION__可以打印模板参数
#define DAMNJONE_LOG(stream,info)(stream\
    <<"FILE: "<<__FILE__<<'\n' \
    << "LINE: " << __LINE__ << '\n'\
    << "FUNCTION: " << __PRETTY_FUNCTION__ << '\n' \
    << "INFORMATION: " << (info) << '\n')

namespace DamnJoneUtil
{
#if defined(__GNUC__)||(__clang__)
    //用于打印任意变量类型的函数(MSVC不适用)
    template<class T>
    std::string get_type_name(T data)
    {
        std::string pretty_function = __PRETTY_FUNCTION__;
        int pos_begin = pretty_function.find("T = ");
        if (pos_begin == std::string::npos)
        {
            return std::string();
        }
        pos_begin += 4;
        int pos_end = pretty_function.find(";");
        if (pos_end == std::string::npos)
        {
            pos_end = pretty_function.find("]");
        }
        if (pos_end == std::string::npos)
        {
            return std::string();
        }
        std::string result = pretty_function.substr(pos_begin, pos_end - pos_begin);
        return result;
    }
#endif

};