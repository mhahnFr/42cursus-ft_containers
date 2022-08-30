//
// Created by Manuel Hahn on 8/30/22.
//

#include "vector.hpp"
#include <vector>
#include <string>
#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> a(std::reverse_iterator<int*>(arr + 9), std::reverse_iterator<int*>(arr));
    ft::vector<int> b(ft::reverse_iterator<int*>(arr + 9), ft::reverse_iterator<int*>(arr));
    for (std::vector<int>::const_iterator it = a.begin(); it != a.end(); ++it) {
        std::cout << *it << std::endl;
    }
    std::cout << "---" << std::endl;
    for (ft::vector<int>::const_iterator it = b.begin(); it != b.end(); ++it) {
        std::cout << *it << std::endl;
    }

    ft::vector<int> is(99, 64);
    for (ft::vector<int>::const_iterator it = is.begin(); it != is.end(); ++it) {
        std::cout << *it << std::endl;
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
