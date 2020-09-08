
//使用折叠表达式实现辅助函数
#include <stdlib.h>
#include <string>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <set>
#include <cassert>

//C++ 11 style recursive sum function
template <typename T>
auto sum_rec(T t)
{
    return t;
}
template <typename T, typename ... Ts>
auto sum_rec(T t, Ts ... ts)
{
    return t + sum_rec(ts ...);
}

//C++ 17 style fold expression
//求和
template <typename ... Ts>
auto sum(Ts ... ts)
{
    return (0 + ... + ts);
}

//C++ 17 style fold expression with constexpr if addition to make it more gerneric
template <typename ... Ts>
auto sum_gereric(Ts ... ts)
{
    if constexpr ((std::is_same<Ts, const char*>::value && ...)){
        //works vith const char* parameters
        return (std::string{} + ... + std::string{ts});
    }
    else if constexpr ((std::is_same<Ts, std::string>::value && ...))
    {
        //works with std::string parameters
        return (std::string{} + ... + ts);
    }
    else 
    {
        //works with integral/floating point types
        return (0 + ... + ts);
    }
}
//或操作
template <typename ... Ts>
auto logical_or(Ts ... ts)
{
    return (... || ts);
}
//按位或
template <typename ...Ts>
auto bitwise_or(Ts ... ts)
{
    return (0 | ... | ts);
}
//  检查是否所有的入参都在指定的范围内
template <typename T, typename ... Ts>
bool within(T min, T max, Ts ... ts)
{
    return ((min <= ts && ts <= max) && ...);
}
//求某个容器范围内，后面折叠参数所有出现的次数和
template <typename C, typename ... Ts>
auto matches(const C &a, Ts ... ts)
{
    return (std::count(std::begin(a), std::end(a), ts) + ...);
}
//检查某个容器插入是否全部成功
template <typename C, typename ... Ts>
bool insert_all(C &s, Ts ... ts)
{
    return (s.insert(ts).second && ...);
}

int main()
{
    assert(sum_rec(1, 2, 3, 4, 5) == 15);
    assert(sum(1, 2, 3, 4, 5) == 15);
    assert (sum(1, 2, 3, 4, 5, 6.5) == 21.5);
    std::string hello{"hello"};
    std::string world{" world"};

    assert(sum_gereric(hello, world) == "hello world");
    assert(sum_gereric(std::string("a"), std::string("b"), std::string("c")) == "abc");
    // auto ressum = sum_gereric(std::string{"abc"}, 2, 4);
    assert(sum_gereric("a", "b", "c") == "abc");
    assert(logical_or() == false);
    assert(logical_or(false, true) == true);

    assert(bitwise_or(1, 2, 4) == 7);
    assert(bitwise_or() == 0);
    
    assert(within(0, 9, 1, 2, 3, 4, 5) == true);
    assert(within(0, 9, 1, 2, 3, 4, 20) == false);

    std::string aaa{"aaa"};
    std::string bcd{"bcd"};
    std::string def{"def"};
    std::string zzz{"zzz"};

    assert(within(aaa, zzz, bcd, def));
    assert(!within(aaa, def, bcd, zzz));

    std::set<int> s;
    assert(insert_all(s, 1, 2, 3) == true);
    assert(insert_all(s, 4, 5, 6, 6) == false);

    assert(1 == matches(std::vector<int>{1, 2, 3, 4}, 2, 5));
    assert(1 == matches(std::initializer_list<int>{1, 2, 3, 4}, 10, 2));
    assert(1 == matches("abcdefg", 'x', 'y', 'z', 'd'));
    assert(4 == matches("abcdefg", 'a', 'c', 'e', 'z'));
    return 0;
}