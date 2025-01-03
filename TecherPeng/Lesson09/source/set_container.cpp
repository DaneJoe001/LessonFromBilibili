#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <unordered_set>

#include <set_container.h>
#include <damnjone_util.h>

template<class T>
void print_array(T array)
{
    for (auto& it : array)
    {
        std::cout << it << '\t';
    }
    std::cout << std::endl;
}

void check_set_container()
{
    std::vector<int> array = { 9,8,5,2,1,1 };
    //set容器去重，并默认从小到大排序
    //set可以高效的按值查找
    //set可以指定比较器(第二个模板参数),默认使用std::less<key>作为值
    std::set<int, std::less<int>>set00 = { 9,8,5,2,1,1 };
    std::set<int> set01 = { 9,8,5,2,1,1 };
    print_array(set01);
    print_array(array);
    std::vector<std::string>array02 = { "arch","any","America","Linux" };
    //set会按字典序排列(std::string重载比较运算符导致)
    //如果是字符数组指针，则会比较地址
    std::set<std::string>set02 = { "arch","any","America","Linux" };
    //set的迭代器不支持+运算
    //迭代器帮手函数
    //使用std::next会自动判断迭代器是否支持'+'运算，不支持则会连续调用++操作
    //std::advance则是+=运算，也支持负数
    //std::prev则是-运算
    //std::distance则是求距离，参数1要小于参数2(可用于求切片元素个数)
    std::set<int>::iterator begin = set01.begin();
    std::set<int>::iterator begin_3 = std::next(begin, 3);
    std::set<int>::iterator begin_2 = std::prev(begin_3, 1);
    size_t distance = std::distance(begin, begin_2);
    std::cout << *(begin_3) << std::endl;
    std::cout << *(begin_2) << std::endl;
    std::cout << distance << std::endl;
    print_array(array02);
    print_array(set02);
    //set会默认按序插入
    //set的insert的返回值为pair<std::iterator,bool>
    //如果失败，会返回已经存在的元素的位置
    auto res = set01.insert(5);
    std::string is_bool = res.second == true ? "true" : "false";
    std::cout << is_bool << std::endl;
    //find函数，查到则返回指向对应元素的迭代器，查不到则返回end()
    //lower_bound(x)找到第一个大于等于x的元素
    //upper_bound(x)找到第一个大于x的元素
    //通过上述函数可以构建迭代器范围区间，进行删除等操作
    //注意开闭区间
    //通过在某些容器中使用另一容器的迭代器，可以构建一个新容器
    //通过set和vector的相互转换可以有效去重
    std::vector<int>vec01(set01.begin(), set01.end());
    std::cout << "vec02: " << std::endl;
    print_array(vec01);
    std::set<int>::iterator pos = set01.find(2);
    if (pos != set01.end())
    {
        std::cout << "Find:" << *pos << std::endl;
    }
    std::set<int>::iterator pos_02 = set01.find(7);
    if (pos_02 == set01.end())
    {
        std::cout << "No values 7!" << std::endl;
        pos_02 = set01.upper_bound(7);
    }
    std::cout << "Find:" << *pos_02 << std::endl;
    //count()函数可以获取集合中指定元素的个数
    //对于去重属性的set,count只会返回0或1
    std::size_t ele_num = set01.count(1);
    std::cout << "The quantity of '1': " << ele_num << std::endl;
    //C++20有contains()函数能判断是否存在对应元素
    //erase函数能去除对应值的元素，并返回成功去除元素的个数
    //erase还支持迭代器作为参数
    //set容器只能先删除再插入，不能直接修改，否则会破坏排序
    //erase也支持区间操作
    set01.erase(5);
    //set01.erase(set01.begin(),set01.end());相当于clear()
    print_array(set01);
    std::set<std::string, int>set03;
    //C++17 基于范围的for循环
    //迭代器写法的简化版
    for (const auto& it : set02)
    {
        std::cout << it << '\t';
    }
    std::cout << std::endl;
    //使用完整版，在切片上有更大的自由度
    //范围循环只会遍历所有范围
    for (auto it = ++(set02.begin());it != --(set02.end());++it)
    {
        std::string value = *it;
        std::cout << value << '\t';
    }
    std::cout << std::endl;
    //使用multiset,会排序但不会去重
    std::multiset<int>multiset_01 = { 9,8,5,2,1,1 };

    print_array(multiset_01);
    //使用equal_range求等值区间边界
    //pair<iterator,iterator>equal_range(int const & val) const;
    //返回的两个迭代器代表区间,找不到时会返回两个end()
    //unordered_set容器能去重但不会排序，具有O(1)的查找效率
    std::unordered_set<int> unordered_set_01 = { 4,5,6,852,2,4,5,87,4,5,9 };

    print_array(unordered_set_01);
    DamnJoneUtil::print_array(std::cout, unordered_set_01, "unordered_set_01");
    DamnJoneUtil::print_array(std::cout, unordered_set_01);



}