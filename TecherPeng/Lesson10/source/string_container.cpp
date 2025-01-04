#include <iostream>
#include <iomanip>
#include <sstream>
#include <string_container.h>

//特殊的重载函数，用于转换C风格字符串至string
std::string operator""_str(const char* s, std::size_t len)
{
    return std::string(s, len);
}

void check_string()
{
    //显式构造
    std::string str01 = "hello!";
    //隐式构造
    std::string str02("world!");
    std::string str03 = str01 + str02;
    //string对象会对短字符串进行优化处理(在栈上存储)
    std::cout << str03 << std::endl;
    //string可以指定大小
    //string实际上相当于char*+size_t的组合
    std::cout << std::string("This is a string", 4) << std::endl;
    //c_str()和data()区别结束字符是否以0结尾
    //c_str()保证返回长度为size()+1
    {
        //C语言风格
        auto func01 = [](const char* name) {};
        //C++风格
        auto func02 = [](std::string name) {};
        //性能高
        auto func03 = [](std::string const& name) {};
        //性能最佳
        auto func04 = [](std::string_view name) {};
    }
    //使用重载函数可以避免套string()
    //标准中的重载为""s
    //使用标准库的重载需要使用using namespace std;
    //更进一步 using namespace std::literals;
    using namespace std::literals;
    std::string new_str = "Hello!"s + "Boy!"_str;
    //数值转换需要显式调用函数
    //宽字符对应版本to_wstring()
    std::string str04 = "Value"_str + std::to_string(100.00);
    std::cout << str04 << std::endl;
    //字符串转数字函数只能处理后面有多余字符的情况
    //stoi可以传回数字结束的位置
    //当开头不是数字时，stoi()会抛出异常
    //浮点数版本stof()可以识别科学计数法
    int value = std::stoi("98"_str);
    std::cout << "Num: " << value << std::endl;
    std::size_t pos = 0;
    int value02 = std::stoi("256null"_str, &pos);
    std::cout << "Num02: " << value02 << " pos: " << pos << std::endl;
    //setprecision()函数可以指定cout输出精度
    std::cout << std::setprecision(3) << 42.11f << std::endl;
    //较为专业的做法(浮点数转字符串)(官方推荐)
    std::stringstream sin;
    sin << std::setprecision(4) << 3.1415926f;
    std::string str05 = sin.str();
    //合并的版本
    std::string str06 = (std::stringstream() << std::setprecision(4) << 3.1415926f).str();
    std::cout << str06 << std::endl;
    //substr()用于截取字符串,第一个参数为起始位置，第二个参数为长度
    //当第二个参数不指定时，默认-1(直接截取到末尾)
    //实质上由于第二个参数类型为size_t，故-1相当于极大数
    //当pos越界，会抛出异常
    std::string origin_str = "0123456789";
    std::string str07 = origin_str.substr(3);
    std::cout << str07 << std::endl;
    std::string str08 = origin_str.substr(3, 3);
    std::cout << str08 << std::endl;
    //find()函数用于查找子字符串的位置，失败则返回-1
    //find()函数的第二个参数可以指定查找的起始位置
    //std::string::npos(相当于(std::size_t)-1)
    //rfind()函数为反向查找
    //find_first_of()查找字符串中第一个满足属于某指定集合的位置
    //find_first_not_of则是不满足某指定集合第一个字符的位置
    //对应反向版本加last find_last_not_of()
    std::size_t pos_5 = origin_str.find('5');
    if (pos_5 != (std::size_t)-1)
    {
        std::cout << "Result: " << pos_5 << std::endl;
    }
    std::size_t pos_43 = origin_str.find_first_of("4378");
    if (pos_43 != (std::size_t)-1)
    {
        std::cout << "Result: " << pos_43 << std::endl;
    }
    std::size_t pos_not_01234 = origin_str.find_first_not_of("01234");
    if (pos_not_01234 != (std::size_t)-1)
    {
        std::cout << "Result: " << pos_not_01234 << std::endl;
    }
    //replace()函数用于替换字符串组成部分
    //第一个参数为起始位置，第二个参数为替换长度，第三个参数为替换的字符串
    //第二个参数指定为std::string::npos或者-1时，会替换末尾所有字符
    //当pos大于字符串长度时，会抛出越界异常
    //replace()函数是就地修改
    origin_str.replace(5, 1, "+++");
    std::cout << origin_str << std::endl;
    //append()追加字符串相当于+=,扩容方式与push_back一致
    //第一个参数为字符串，第二个参数为追加长度
    //第一个参数针对C风格字符串和string对象会有不同的操作
    std::string str09 = "123";
    str09.append("456");
    str09.append("78900000", 3);
    str09 += "8888";
    std::cout << str09 << std::endl;
    //使用切片string_view()可以进行优化
    std::string str10 = "abc";
    str10 += std::string_view("def");
    std::cout << str10 << std::endl;
    //insert()插入函数，会插入到pos,pos+1之间
    //这里的pos不是下标,而是字符位序
    str10.insert(3, "000");
    std::cout << str10 << std::endl;
    //C++20新增starts_with(str)函数和ends_with(str)函数
    //可以很方便的用来判断后缀等操作
    //版本不支持的情况下可以使用substr进行替换
#if __cplusplus==202002L
    std::string str11 = "text.txt";
    if (str11.ends_with("txt"))
    {
        std::cout << "The string is ends with: " << "txt" << std::endl;
    }
#endif
    //string_view()为C++17引入的弱引用胖指针(指针+长度)
    //弱引用不影响原对象，是浅拷贝
    //string_view()是不可写入的
    //string_view()与原字符串共享一片内存(避免了拷贝)
    std::string_view = std::string_view(str10);
    //remove_prefix(n)和remove_suffix(n)为就地修改，安全欠佳
    //substr()会有拷贝行为，会进行越界检查

}