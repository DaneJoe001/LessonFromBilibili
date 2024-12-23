#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <cmath>
//#include <generator>
#include <format>
#include <cpp_features.h>

//如果不使用Lambda表达式，必须在外部定义变量用来存储值
static int old_sum = 0;

void func01(int vi)
{
    old_sum += vi;
}

void check_features_of_cpp()
{
    std::vector<int>vec01 = { 0,1,2,3,4,5,6,7,8,9 };
    //std::for_each(v.begin(), v.end(), func01);

    int sum01 = 0;
    //[&](int vi) {sum += vi;}[&]可以使用引用的方式捕获外部变量
    std::for_each(vec01.begin(), vec01.end(), [&](auto value) {sum01 += value;});
    std::cout << "The sum of vec01: " << sum01 << std::endl;

    //C++17标准，不用指定int类型,可以根据参数列表进行推断
    //C++17 CTAD compile-time argument deduction
    std::vector vec02 = { 1,2,3,4,5 };
    //此函数默认从0开始相加
    int sum02 = std::reduce(vec02.begin(), vec02.end());

    //第三个参数为初始值，从1开始累加vec02的元素
    int result01 = std::reduce(vec02.begin(), vec02.end(), 1, std::plus{});

    //第四个函数可以自定义
    int result02 = std::reduce(vec02.begin(), vec02.end(), 1, [](int num1, int num2) {return num1 * num2;});

    std::cout << "The sum of vec02: " << sum02 << std::endl;
    std::cout << "The sum of result01: " << result01 << std::endl;
    std::cout << "The sum of result02: " << result02 << std::endl;

    //C++20引入区间
    //CMake暂时不支持C++20 modules
    //C++20允许函数参数为自动推断
    // std::generator<int> func02(auto&& vec)
    // {
    //     for (auto&& value : vec
    //         | std::views::filter([](auto&& x) { return x > 0; })
    //         | std::views::transform([](auto&& x) { return sqrtf(x); })
    //         )
    //     {
    //         co_yield value;
    //     }
    // }
    std::vector vec03 = { 4,3,2,1,0,-1,-2 };

    std::cout << "The result03 by format: ";

    //从上至下依次处理
    for (auto&& value : vec03
        /*过滤器：过滤出大于0的数*/
        | std::views::filter([](auto&& x) { return x > 0; })
        /*对大于0的数开根号求值*/
        | std::views::transform([](auto&& x) { return sqrtf(x); })
        )
    {
        std::cout << std::format("{} ", value);
    }
    std::cout << std::endl;

    // sdt::cout << "The result04: ";
    // for (auto&& value : func02(vec03))
    // {
    //     std::format_to(std::cout, "num{} ", value);
    // } 
    // std::cout << std::endl;
}