#include <template_example.h>
#include <template_and_function.h>
#include <teacher_peng_util.h>

void check_different_template()
{
    std::cout << "Type int: " << twice<int>(21) << std::endl;
    std::cout << "Type float: " << twice<float>(3.14f) << std::endl;
    std::cout << "Type double: " << twice<double>(2.718) << std::endl;
    std::cout << "Type string: " << twice<std::string>(std::string("Hey!")) << std::endl;

    show_times("one");
    show_times<3>(42);
    show_times<4>('%');

    std::vector<int>array01 = { 1,2,3,4,5,6 };
    std::cout << "Sum of array01: " << sum(array01) << std::endl;
    std::vector<float>array02 = { 1.23f,2.34f,3.45f,4.56f };
    std::cout << "Sum of array01: " << sum(array02) << std::endl;

    std::cout << array01 << std::endl;
    std::cout << array02 << std::endl;
}

void check_compile_time_contexper_function()
{
    //编译期constexper的表达式，一般无法调用其他函数
    //使用constexper得确保能在编译期求值
    //constexper函数必须是内联的，不能分离实现
    //constexper函数不能调用non-constexper函数
    //标准库中如std::min也是编译期常量函数

    std::cout << sumto<true>(4) << std::endl;
    std::cout << sumto<false>(4) << std::endl;

}

void check_auto_and_reference()
{
    //引用即左值，对应着具有长声明周期的变量
    //右值通常对应表达式，代表计算过程中临时生成的中间变量
    int data01 = 20241224;
    //自动推导也可以用来定义引用
    auto& ref = data01;
    std::cout << "Changing before: " << data01 << std::endl;
    ref = 20240125;
    std::cout << "After changing: " << data01 << std::endl;
    //C++中 int&&能自动转换成int const&
    std::cout << "Type name: " << cpp_type_name<float> << std::endl;
    std::cout << "Type name: " << cpp_type_name<decltype(data01)> << std::endl;
    decltype(data01) data02 = 20240115;
    std::cout << "Make variable by decltype: " << data02 << std::endl;

    std::cout << std::boolalpha;
    //比较类型
    std::cout << "Type comparison: " << std::is_same_v<int const*, const int*> << std::endl;
    //std::remove_const_t<int const>可用于移除const
    std::cout << "Type comparison: " << std::is_same_v<std::remove_const_t<int const>, int> << std::endl;
    std::cout << "Type comparison: " << std::is_same_v<std::decay_t<int[]>, int*> << std::endl;
    std::cout << std::noboolalpha;

    //万能推导func()的返回值类型
    decltype(auto)func_ptr_01 = func01();
    //等价于
    decltype(func01())func_ptr_02 = func01();
    //decltype能自动匹配引用等类型，auto&只能匹配引用
}

#ifdef PERFECT_RETURN
//代理模式，完美转发函数返回值
decltype(auto) at(size_t i)const
{
    return m_internal_class.at(i);
}
#endif

void function_change()
{
#ifdef FUNCTION_CHANGE
    //旧版本
    std::decay<int>::type;
    std::is_same<int, int>::value;
    //C++14 引入的一个别名模板
    std::decay_t<int>;
    //C++17 引入的一个变量模板
    std::is_same_v<int, int>;
#endif
}