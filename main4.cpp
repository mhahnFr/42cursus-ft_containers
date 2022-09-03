#include <iostream>
#include <string>
#include "vector.hpp"

int main() {
    std::string strings[] = {
        "huhu",
        "some!",
        "strings"
    };
    ft::vector<std::string> v(strings, strings + 3);
    ft::vector<std::string>::iterator it = v.begin() + 1;
    ft::vector<std::string>::const_iterator it2 = v.begin();
    std::cout << std::boolalpha << (it == it2) << std::endl;
    for (ft::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i) {
        std::cout << (i == it) << std::endl;
    }
}
