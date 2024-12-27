#include <iostream>
#include <cmath>
#include <normal_container.h>

//tuple可以用于多返回值
std::tuple<bool, float>mysqrt_01(float x)
{
    if (x > 0.f)
    {
        //return表达式可以使用{}初始化
        //不必使用std::tuple;
        return { true,std::sqrt(x) };
    }
    else
    {
        return { false,0.0f };
    }
}

//optional容器
std::optional<float> mysqrt_02(float x)
{
    if (x > 0.f)
    {
        return std::sqrt(x);
    }
    else
    {
        //返回无效选项
        return std::nullopt;
    }
}

void check_tuple()
{
    //tuple容器可以将不同元素的类型打包
    auto tup = std::tuple<int, float, char>(3, 3.14f, 'h');
    //使用std::get<index>(tup)可以获取对应元素
    std::cout << "First value:" << std::get<0>(tup) << std::endl;
    std::cout << "Second value:" << std::get<1>(tup) << std::endl;
    std::cout << "Third value:" << std::get<2>(tup) << std::endl;

    //C++17tuple可以自动推断类型
    auto tup_in_cpp17 = std::tuple(2, '5', 3.24);
    std::cout << "First value:" << std::get<0>(tup_in_cpp17) << std::endl;
    std::cout << "Second value:" << std::get<1>(tup_in_cpp17) << std::endl;
    std::cout << "Third value:" << std::get<2>(tup_in_cpp17) << std::endl;

    //tuple的结构化绑定，解包tuple，顺序赋值
    //使用auto& ,auto const &可以解包为引用和常引用
    auto [first, second, third] = tup_in_cpp17;
    std::cout << "Values in tup: " << first << '\t' << second << '\t' << third << std::endl;
    //结构化绑定为万能推导
    auto&& [x, y, z] = tup;
    //decltype(auto)[x,y,z]=tup;错误

    //结构化绑定可以解包任意自定义类；
    //std::get不支持自定义类
    Test test01 = { 100,"Scores" };
    auto [value01, value02] = test01;
    std::cout << "Value in test01: " << value01 << '\t' << value02 << std::endl;



}

void check_optional()
{
    auto ret = mysqrt_02(3.f);
    //if(ret)和if (ret.has_value())在此处是等价的
    if (ret.has_value())
    {
        std::cout << "Result: " << ret.value() << std::endl;
    }
    else
    {
        std::cout << "Invalid calling!\n";
    }

    auto ret02 = mysqrt_02(-3.14f);
    //指定缺省值
    std::cout << "Result: " << ret02.value_or(20240101) << std::endl;
    //当value为空时会抛出异常
    //异常类型为std::bad_optional_access
    //std::cout << "Result: " << ret02.value() << std::endl;
}

void print_01(std::variant<int, float>const& value)
{
    //使用std::holds_alternative可以判断是不是存储的对应类型
    if (std::holds_alternative<int>(value))
    {
        std::cout << "Value: " << std::get<int>(value) << std::endl;
    }
    else if (std::holds_alternative<int>(value))
    {
        std::cout << "Value: " << std::get<float>(value) << std::endl;
    }
}

void print_02(std::variant<int, float>const& value)
{
    //使用value.index()判断当前存储的对应类型
    if (value.index() == 0)
    {
        std::cout << "Value: " << std::get<0>(value) << std::endl;
    }
    else if (value.index() == 1)
    {
        std::cout << "Value: " << std::get<1>(value) << std::endl;
    }
}

void print_03(std::variant<int, float>const& value)
{
    //std::visit可以实现variant的批量匹配
    //此种实现的模式称为静态多态，与虚函数、抽象类的动态多态相对
    //优点：性能开销小，存储大小固定
    //缺点：类型固定，不能运行时扩充
    std::visit([&](auto const& temp)
        {
            std::cout << temp << std::endl;
        }, value);
}

void print_03(std::variant<int, float>const& value01,
    std::variant<int, float>const& value02)
{
    //std::visit可以有多个variant参数
    //匿名表达式的参数列表要与之匹配
    //std::visit会自动罗列出所有的排列组合
    //编译速度为平方级，但运行速度为0(1)
    std::visit([&](auto const& temp01, auto const& temp02)
        {
            std::cout << "Value: " << temp01 << std::endl;
            std::cout << "Value: " << temp02 << std::endl;
        }, value01, value02);
}

void check_variant()
{
    //给variant赋值不需要像普通结构体一样，只需要'='即可
    std::variant<int, float>value = 3;
    value = 3.14f;
    //使用std::get获取vairiant中的数据
    //如果数据类型不匹配的化，std::get调用会出错
    std::cout << "Value: " << std::get<float>(value) << std::endl;
    print_01(value);
    print_02(value);

    std::variant<int, float>value02 = 3;
    print_03(value, value02);
}
