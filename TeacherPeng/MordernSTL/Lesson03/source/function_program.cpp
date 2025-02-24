#include <iostream>
#include <vector>
#include <set>
#include <function_program.h>

void func02()
{
    std::cout << "This is func01!" << std::endl;
}

void func03(int num)
{
    std::cout << "func03 with num " << num << "!" << std::endl;
}

//函数作为参数
void call_twice_01(void func())
{
    std::cout << "First call:";
    func();
    std::cout << "Second call:";
    func();
}

//带有参数的函数作为参数
void call_twice_02(void func(int))
{
    std::cout << "First call:";
    func(2);
    std::cout << "Second call:";
    func(5);
}

void print_float(float num)
{
    std::printf("Float %f\n", num);
}

void print_int(int num)
{
    std::printf("Int %d\n", num);
}

//利用模板进行优化
template <class Func>
//声明为Func const& func避免不必要的拷贝
void call_twice_03(Func const& func)
{
    func(0);
    func(1);
}

//使用lambda表达式作为返回值
//由于lambda表达式的匿名类型，返回值需要由auto自动推导
auto func04()
{
    return[](int n)
        {
            return n * 2;
        };
}

auto func05(int value)
{
    //由于lambda表达式作为返回值
    //value会先出栈
    //如果使用[&]捕获引用则会失效
    //使用[&]需要保证lambda对象的生命周期不超过引用的寿命
    //使用[=]会造成拷贝，尽量使用[&]
    return[=](int num)
        {
            return num * value;
        };
}

//function容器,尖括号中为返回类型和参数列表
//补充：std::any能擦除类型信息，只保留引用
void call_twice_04(std::function<int(int)> const& func)
{
    std::cout << "First call:";
    func(0);
    std::cout << "Second call:";
    func(1);
    std::cout << "Size of func:" << sizeof(func) << std::endl;
}

//无捕获的lambda可以传为函数指针
//即可以适应C语言的API如pthread函数
void call_twice_05(int func(int))
{
    std::cout << "First call:";
    func(0);
    std::cout << "Second call:";
    func(1);
    std::cout << "Size of func:" << sizeof(func) << std::endl;
}

template<class Func>
void fetch_data(Func const& func)
{
    for (int i = 0;i < 5;i++)
    {
        func(i);
        func(i + 0.5f);
    }
}

void use_lambda_function()
{
    std::vector<int> res_i;
    std::vector<float> res_f;
    auto fetch = [&](auto const& x)
        {
            //获取x的类型，然后根据类型选择不同的处理方式
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, int>)
            {
                res_i.push_back(x);
            }
            else if constexpr (std::is_same_v<T, float>)
            {
                res_f.push_back(x);
            }
            //此类模板属于C++ type traits
        };
    //在fetch_data函数内部使用不同的值调用fetch函数
    //函数作为变量传入时，函数指针本身不能携带参数
    //想传递参数，必须使用另一个函数参数或者在函数内部固定调用
    fetch_data(fetch);

    std::vector<int> array = { 1,4,2,8,5,7,1,4 };
    int target = 5;
    //使用();结尾可以作为立即调用函数
    //通过立即调用，lambda 函数会执行并返回结果
    //结果可以被赋值给 index 变量。
    int index = [&]
        {
            for (int i = 0;i < array.size();i++)
            {
                if (array[i] == target)
                {
                    return i;
                }
            }
            return -1;
        }();
    std::cout << "Index of target in array: " << index << std::endl;

    //用lambda函数可以实现匿名递归
    std::set<int> visited;
    auto dfs = [&](auto const& dfs, int index)->void
        {
            //用于检查当前索引是否已经被访问
            if (visited.find(index) == visited.end())
            {
                //插入标记为以访问
                visited.insert(index);
                std::cout << "Recent index: " << index << std::endl;
                int next = array[index];
                dfs(dfs, next);
            }
        };
    dfs(dfs, 0);
}

void check_function_call()
{
    call_twice_01(func02);
    call_twice_02(func03);
    call_twice_03(print_float);
    call_twice_03(print_int);
    //使用lambda表达式的版本,C++11引入
    //优点，不用被迫添加全局函数，避免了命名污染
    auto lambda_func = [](int num)
        {
            printf("Number %d\n", num);
        };
    call_twice_02(lambda_func);
    //带有返回值的lambda表达式,使用后置返回值
    //返回值不显式声明，亦可自动推导
    auto twice = [](int num)->int
        {
            return num * 2;
        };
    std::cout << "2*2: " << twice(2) << std::endl;
    //捕获变量的lambda表达式
    //函数可以引用定义位置所有的变量
    //该特性在函数式编程中称为闭包
    //捕获为可变引用，即可在lambda表达式中修改
    int times = 4;
    int counter = 0;
    auto twice_2 = [&](int num)
        {
            counter++;
            return num * times;
        };
    std::cout << "4*2: " << twice_2(2) << std::endl;
    std::cout << "Counter of calling twice_2: " << counter << std::endl;

    //使用auto作为参数与模板类型相似
    //带auto参数的lambda表达式，和模板函数一样
    //具有惰性，多次编译的特性
    auto twice_3 = [](auto num)->int
        {
            return num * 2;
        };
    call_twice_05(twice_3);
    //C++20新特性
    //除了auto亦可以使用模板参数
#if _cplusplus >= 202002L
    auto twice_4 = []<class T>(T num)
    {
        return num * 2;
    };
#endif

}