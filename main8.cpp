//
// Created by Manuel Hahn on 9/30/22.
//

#include "map.hpp"
#include <string>
#include <iostream>

#define NAMESPACE ft

typedef NAMESPACE::map<std::string, std::string> strmap;

#define PRINT_LINE(text, var) (std::cout << (text) << " " << (var) << std::endl)

#define PRINT_ALL(c) \
std::cout << "Content:" << std::endl;                     \
for (strmap::const_iterator it = (c).begin(); it != (c).end(); ++it) { \
    std::cout << "K: " << it->first << ", V: " << it->second << std::endl; \
}\
std::cout << std::endl;

int main() {
    strmap m;

    strmap::size_type size = m.erase("");
    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    m.insert(NAMESPACE::make_pair("", ""));
    m.insert(NAMESPACE::make_pair("123", "kjhgfdsdffghsfghdfgh"));
    m.insert(NAMESPACE::make_pair("1234", "gfdsadgg"));
    m.insert(NAMESPACE::make_pair("123456789123456789123456789", "49857459898674568464"));
    m.insert(NAMESPACE::make_pair("0", "2345456456456456"));
    m.insert(NAMESPACE::make_pair("", ""));
    m.insert(NAMESPACE::make_pair("", "9459845984598498"));
    m.insert(NAMESPACE::make_pair("000000000000000000000000", "1111111111111111111111111111"));

    size = m.erase("1");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    size = m.erase("123");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    size = m.erase("123");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    size = m.erase("");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    size = m.erase("1234");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    size = m.erase("123456789123456789123456789");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    size = m.erase("000000000000000000000000");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    size = m.erase("0");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);

    size = m.erase("000000000000000000000000");

    PRINT_LINE("Erased?:", size);
    PRINT_ALL(m);
}
