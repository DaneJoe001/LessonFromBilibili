#pragma once

#include <functional>

//C++条件编译版本宏
//#if __cplusplus == 201103L
// C++98: 199711L
// C++11 : 201103L
// C++14 : 201402L
// C++17 : 201703L
// C++20 : 202002L

void func02();

void func03(int num);

void call_twice_01(void func());

void call_twice_02(void func(int));

void print_float(float num);

void print_int(int num);

void call_twice_04(std::function<int(int)> const& func);

void call_twice_05(int func(int));

void use_lambda_function();

void check_function_call();