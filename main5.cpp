//
// Created by Manuel Hahn on 9/15/22.
//

#include <iostream>
#include <string>
#include "map.hpp"
#include <map>

int main() {
    ft::map<int, std::string> m;

    std::cout << std::boolalpha << (m.begin() == m.end()) << std::endl;

    try {
        std::cout << std::boolalpha << m.at(5) << std::endl;
    } catch (std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }
    m.insert(ft::make_pair(5, "ArschA"));
    std::cout << std::boolalpha << (m.begin() == m.end()) << std::endl;
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
// 2 3 4 5 6 22 33 44 54
    const ft::map<int, std::string>::const_reverse_iterator end = ft::map<int, std::string>::const_reverse_iterator(m.find(2));
    for (ft::map<int, std::string>::const_reverse_iterator it = ft::map<int, std::string>::const_reverse_iterator(m.find(54)); it != end; ++it) {
        std::cout << it->second << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::boolalpha << (m.begin() == m.end()) << std::endl;

    std::cout << std::endl;
    for (ft::map<int, std::string>::const_iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->second << "," << std::endl;
    }
    std::cout << std::endl;

    for (ft::map<int, std::string>::const_reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
        std::cout << it->second << "," << std::endl;
    }
    std::cout << std::endl;

    m2.clear();
    m2.insert(m.begin(), m.end());
    for (ft::map<int, std::string>::const_iterator it = m2.begin(); it != m2.end(); ++it) {
        std::cout << it->second << "," << std::endl;
    }

    ft::map<int, std::string> a1, a2;
    a1 = a2;
    for (ft::map<int, std::string>::iterator it = a1.begin(); it != a1.end(); ++it) {
        std::cout << "K: " << it->first << " V: " << it->second << " ";
    }
    std::cout << std::endl;

    const int isaLength = 64;
    ft::pair<int, std::string> isa[64];

    //ft::map<int, std::string> a3 = ft::map<int, std::string>(isa, isa + isaLength);
    a2 = ft::map<int, std::string>(isa, isa + isaLength);

    for (ft::map<int, std::string>::iterator it = a2.begin(); it != a2.end(); ++it) {
        std::cout << "K: " << it->first << " V: " << it->second << " ";
    }
    std::cout << std::endl;

    std::cout << a2.max_size() << std::endl;
    std::cout << std::map<int, std::string>().max_size() << std::endl;
    
    std::cout << m2.insert(m2.begin(), ft::make_pair(5, "Arsch5"))->second << std::endl;
}
