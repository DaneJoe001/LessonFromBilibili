#include <iostream>
#include <map>
#include <string>

#include <map_container.h>

using namespace std::literals;

void check_map_container()
{
    //当使用字符串作为key时，建议不要使用C风格字符串
    //由于map容器比较key采取的时==比较
    //所以如果key时const char*的话，比较的是指针，而不是内容
    //C++11引入列表初始化
    std::map<std::string, int>map01 = { { "key1", 1 } };
    map01.insert({ "key2",2 });
    //当使用[]访问map数据时，如果键值不存在会创建新的键值对并插入
    //使用at()则只会访问已有的数据
    //故建议使用at函数进行访问读取
    //可以利用[]的特性，元素不存在时创建对元素进行计数处理
    std::cout << map01["key2"] << std::endl;
    std::cout << map01.at("key1") << std::endl;
    map01["key3"] = 3;
}