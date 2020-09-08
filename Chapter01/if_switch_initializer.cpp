#include <iostream>
#include <cstdio>
#include <map>
#include <string>
// C++11
template <typename T>
void print_charcount_cpp11(const T &map, char c)
{
    const auto itr(map.find(c));
    if(itr != map.end()){
        std::cout << "There are " << itr->second << " " << c << " characters." << "\n";
    }
    else
    {
        std::cout << "There are " << 0 << " " << c << " characters." << "\n";
    }
    
}
// C++ 17 变量的作用域限制在if条件语句中
template <typename T>
void print_charcount_cpp17(const T &map, char c)
{
    if (const auto itr(map.find(c)); itr != map.end()){
        std::cout << "There are " << itr->second << " " << c << " characters." << "\n";
    }
    else
    {
        std::cout << "There are " << 0 << " " << c << " characters." << "\n";
    }
}

int main()
{
    {
        std::map<char, size_t> character_map {{'a', 10}, {'b', 20}};
        print_charcount_cpp11(character_map, 'a');
        print_charcount_cpp11(character_map, 'c');

        print_charcount_cpp17(character_map, 'a');
        print_charcount_cpp17(character_map, 'c');
    }
    // switch
    {
        std::cout << "please enter a character: ";
        switch (char c(getchar()); c)
        {
        case 'a' ... 'z':
            std::cout << "You entered a lower case letter: " << c << "\n";
            break;
        case 'A' ... 'Z':
            std::cout << "You entered a lower upper letter: " << c << "\n";
            break;
        default:
            std::cout << "You entered something else: " << c << "\n";
            break;
        }
    }

    return 0;
}
