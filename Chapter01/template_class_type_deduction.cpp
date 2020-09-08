#include <tuple>
#include <string>
#include <type_traits>
#include <iostream>
#include <vector>

template <typename T1, typename T2, typename T3>
class my_wrapper{
    T1 t1;
    T2 t2;
    T3 t3;
public:
    my_wrapper(T1 t1_, T2 t2_, T3 t3_) : t1(t1_), t2(t2_), t3(t3_){}
};

template <typename T>
struct sum {
    T value;
    template <typename ... Ts>
    sum(Ts&& ... values) : value((values + ...)) {}
};

template <typename ... Ts>
sum(Ts&& ... ts) -> sum <std::common_type_t<Ts ...>>;

int main()
{
    my_wrapper wrap(123, 4.56, std::string{"foo"});
    /*
    *
    * {}与()调用构造函数初始化的方式，不同点在于{}没有类型的隐式转换，比如int x(1.2);和int x = 1.2;
    * 通过静默的对浮点值进行向下取整，然后将其转换为整型，从而将x的值初始化为1。
    * 相反的，int x{1.2};将会遇到编译错误，初始化列表中的初始值，需要与变量声明的类型完全匹配。
    Note:
    哪种方式是最好的初始化方式，目前业界是有争议的。括号初始化的粉丝们提出，使用括号的方式非常直观，直接可以调用构造函数对变量进行初始化，并且代码行不会做多于的事情。
    另一方指出，使用{}括号将会是匹配构造函数的唯一选择，这是因为使用()进行初始化时，会尝试匹配最符合条件的构造函数，并且还会对初始值进行类型转换，然后进行匹配(这就会有处理构造函数二义性的麻烦)。
    */
    std::pair pair(123, std::string{"string"});
    std::tuple tuple(123, 4.56, std::string("string"));

    sum s {1u, 2.0, 3, 4.0f};
    sum string_sum {std::string("abc"), "def"};
    // sum complex_sum {std::string("abc"), 3, 5, 6}; //no matching function for call to ‘sum(std::__cxx11::string, int, int, int)’
    std::cout << s.value << "\n";
    std::cout << string_sum.value << "\n";
    std::vector<int> copy = {1, 2, 3, 4, 5, 6};
    for (auto &n : copy)
    {
        n += 3;
    }
    std::cout << "copy = " << copy[2] << "\n";
    return 0;
}