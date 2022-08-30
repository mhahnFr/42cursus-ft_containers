//
// Created by Manuel Hahn on 8/30/22.
//

#include "vector.hpp"
#include <vector>
#include <string>
#include <iostream>

int main() {
    ft::vector<int> is(99, 64);
    for (ft::vector<int>::const_iterator it = is.begin(); it != is.end(); ++it) {
        std::cerr << *it << std::endl;
    }
    std::vector<std::string> stdVector;
    ft::vector<std::string>  ftVector;

    std::string strings[] = {
            "Arsch",
            "Huhu",
            "Sieh mal einer an",
            "soo ...",
            "VIELE",
            "Strings!"
    };

    stdVector.insert(stdVector.begin(), strings, strings + 6);
    ftVector.insert(ftVector.begin(), strings, strings + 6);

    for (ft::vector<std::string>::const_reverse_iterator it = ftVector.rbegin(); it != ftVector.rend(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "----" << std::endl;
    for (std::vector<std::string>::const_reverse_iterator it = stdVector.rbegin(); it != stdVector.rend(); ++it) {
        std::cout << *it << std::endl;
    }
    for (ft::vector<std::string>::reverse_iterator it = ftVector.rbegin(); it != ftVector.rend(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "----" << std::endl;
    for (std::vector<std::string>::reverse_iterator it = stdVector.rbegin(); it != stdVector.rend(); ++it) {
        std::cout << *it << std::endl;
    }
}
