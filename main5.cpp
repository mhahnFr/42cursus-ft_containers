//
// Created by Manuel Hahn on 9/15/22.
//

#include <iostream>
#include <string>
#include "map.hpp"
#include <map>

int main() {
    ft::map<int, std::string> m;

    try {
        std::cout << std::boolalpha << m.at(5) << std::endl;
    } catch (std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }
    m.insert(ft::make_pair(5, "Arsch"));
    std::cout << std::boolalpha << m.at(5) << std::endl;
    try {
        std::cout << std::boolalpha << m.at(6) << std::endl;
    } catch (std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }
    m.insert(ft::make_pair(6, "Arsch2"));
    std::cout << std::boolalpha << m.at(6) << std::endl;
    m[54] = "Arsch3";
    std::cout << m.at(54) << " : " << m[5] << std::endl;

    std::cout << std::endl << std::endl;

    ft::map<int, std::string> m2 = m;
    try {
        std::cout << std::boolalpha << m2.at(5) << std::endl;
    } catch (std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << std::boolalpha << m2.at(5) << std::endl;
    try {
        std::cout << std::boolalpha << m2.at(6) << std::endl;
    } catch (std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << std::boolalpha << m2.at(6) << std::endl;
    m2[54] = "Arsch3";
    std::cout << m2.at(54) << " : " << m2[5] << std::endl;
}
