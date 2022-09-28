//
//  main6.cpp
//  ft_c
//
//  Created by Manuel Hahn on 28.09.22.
//  Copyright © 2022 mhahnFr. All rights reserved.
//

#include "map.hpp"
#include <map>
#include <iostream>
#include <string>

#define NAMESPACE ft
#define intmap NAMESPACE::map<int, std::string>

#define PRINT_PAIR_REF(pair) \
std::cout << "K: " << (pair).first << ", V: " << (pair).second << std::endl

int main() {
    intmap m;

    intmap::iterator it = m.insert(m.end(), NAMESPACE::make_pair(64, "Gamepak"));

    PRINT_PAIR_REF(*it);

    it = m.insert(m.end(), NAMESPACE::make_pair(64, "Test"));

    PRINT_PAIR_REF(*it);

    it = m.insert(m.end(), NAMESPACE::make_pair(100, "100$"));

    PRINT_PAIR_REF(*it);

    it = m.end();
    --it;

    it = m.insert(it, NAMESPACE::make_pair(100, "12345"));

    PRINT_PAIR_REF(*it);

    it = m.insert(it, NAMESPACE::make_pair(69, "420"));

    PRINT_PAIR_REF(*it);
}
