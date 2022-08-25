//
// Created by Manuel Hahn on 7/8/22.
//

#include <iostream>
#include <vector>
#include "vector.h"

template <typename Vector>
void printVectorStats(const Vector & vector) {
    std::cout << "Size:     " << vector.size()     << std::endl
              << "Capacity: " << vector.capacity() << std::endl
              << "Elements: " << std::endl;
    for (typename Vector::const_iterator it = vector.begin(); it != vector.end(); ++it) {
        std::cout << it - vector.begin() << ": " << *it << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "\033[33;1m" << "ft::vector" << "\033[0m" << std::endl << std::endl;
    ft::vector<std::string> strings(5);

    strings.clear();
    strings.push_back("Hi");
    strings.push_back("test");
    strings.push_back("count the strings");

    printVectorStats(strings);
    strings.pop_back();
    printVectorStats(strings);

    std::cout << *strings.erase(std::find(strings.begin(), strings.end(), "Hi")) << std::endl;
    printVectorStats(strings);

    strings.erase(strings.begin());
    printVectorStats(strings);

    std::cout << "\033[34;1m" << "std::vector" << "\033[0m" << std::endl << std::endl;

    std::vector<std::string> stdStrings(5);

    stdStrings.clear();
    stdStrings.push_back("Hi");
    stdStrings.push_back("test");
    stdStrings.push_back("count the strings");

    printVectorStats(stdStrings);
    stdStrings.pop_back();
    printVectorStats(stdStrings);

    std::cout << *stdStrings.erase(std::find(stdStrings.begin(), stdStrings.end(), "Hi")) << std::endl;
    printVectorStats(stdStrings);

    stdStrings.erase(stdStrings.begin());
    printVectorStats(stdStrings);
}
