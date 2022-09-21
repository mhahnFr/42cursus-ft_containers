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
    m.insert(ft::make_pair(5, "ArschA"));
    std::cout << std::boolalpha << m.at(5) << std::endl;
    try {
        std::cout << std::boolalpha << m.at(6) << std::endl;
    } catch (std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }
    m.insert(ft::make_pair(6, "ArschB"));
    std::cout << std::boolalpha << m.at(6) << std::endl;
    m[54] = "ArschC";
    std::cout << m.at(54) << " : " << m[5] << std::endl;

    std::cout << std::endl << std::endl;

    const ft::map<int, std::string> m2 = m;
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
    std::cout << m2.at(54) << std::endl;
    std::cout << m2.find(5)->second << std::endl;
    std::cout << std::endl;

    m[44] = "Arsch44";
    m[22] = "Arsch22";
    m[33] = "Arsch33";
    m[4] = "Arsch4";
    m[2] = "Arsch2";
    m[3] = "Arsch3";

    std::cout << m.at(44) << std::endl;
    std::cout << m.at(22) << std::endl;
    std::cout << m.at(33) << std::endl;
    std::cout << std::endl;

    const ft::map<int, std::string>::iterator end = m.find(54);
    for (ft::map<int, std::string>::iterator it = m.find(2); it != end; ++it) {
        std::cout << it->second << std::endl;
    }
    std::cout << std::endl;
}
