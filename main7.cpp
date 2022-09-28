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
    
    m[1] = "Arsch1";
    print(m);
    m.erase(1);
    print(m);
    
    m[35] = "Arsch35";
    m[20] = "Arsch20";
    m[21] = "Arsch21";

    print(m);
    
    //m.erase(20);
}
