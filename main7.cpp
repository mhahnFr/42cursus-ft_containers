//
//  main7.cpp
//  ft_c
//
//  Created by Manuel Hahn on 28.09.22.
//  Copyright © 2022 mhahnFr. All rights reserved.
//

#include "map.hpp"
#include <string>
#include <iostream>

template<class amp>
static inline void print(const amp & m) {
    for (typename amp::const_iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << "K: " << it->first << ", V: " << it->second << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    ft::map<int, std::string> m;

    /*for (int i = 0; i < 20; ++i) {
        m[i] = "Arsch";
    }
    print(m);
    m.erase(15);
    print(m);+*/

    m[1] = "Arsch1";
    print(m);
    std::cout << "Erasing: 1" << std::endl;
    m.erase(1);
    print(m);
    
    m[1] = "Arsch1";
    m[2] = "Arsch2";
    print(m);
    std::cout << "Erasing: 2" << std::endl;
    m.erase(2);
    print(m);
    
    m[2] = "Arsch2";
    print(m);
    std::cout << "Erasing: 1" << std::endl;
    m.erase(1);
    print(m);
    
    m[35] = "Arsch35";
    m[20] = "Arsch20";
    m[21] = "Arsch21";

    print(m);

    std::cout << "Erasing: 20" << std::endl;
    m.erase(20);
    print(m);

    std::cout << "Erasing: 21" << std::endl;
    m.erase(21);
    print(m);
    m[21] = "Arsch21";
    print(m);
    std::cout << "Erasing: 2" << std::endl;
    m.erase(2);
    print(m);
    m[2] = "Arsch2";
    print(m);
    std::cout << "Erasing: 35" << std::endl;
    m.erase(35);
    print(m);
    m[35] = "Arsch35";
    print(m);

    for (ft::map<int, std::string>::const_iterator it = --m.end(); it != --m.begin(); --it) {
        std::cout << "K: " << it->first << ", V: " << it->second << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Erasing: begin() to end()" << std::endl;
    m.erase(m.begin(), m.end());
    print(m);
}
