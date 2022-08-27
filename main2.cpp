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
    std::vector<std::string> s;
    for (char c = 'a'; c != 'z'; ++c) {
        char cs[2] = {c, '\0' };
        s.push_back(cs);
    }

    std::cout << "\033[33;1m" << "ft::vector" << "\033[0m" << std::endl << std::endl;
    /*ft::vector<std::string> strings(5);

    strings.clear();*/
    ft::vector<std::string> strings;
    strings.push_back("Hi");
    strings.push_back("test");
    strings.push_back("count the strings");
    strings.push_back("Some arsches");
    printVectorStats(strings);

    std::cout << *strings.erase(strings.begin() + 1) << std::endl;
    printVectorStats(strings);

    strings.pop_back();
    printVectorStats(strings);

    std::cout << *strings.erase(std::find(strings.begin(), strings.end(), "Hi")) << std::endl;
    printVectorStats(strings);

    strings.erase(strings.begin());
    printVectorStats(strings);

    strings.insert(strings.begin(), "A");
    printVectorStats(strings);
    strings.insert(strings.begin(), "B");
    printVectorStats(strings);
    strings.insert(strings.begin() + 1, "C");
    printVectorStats(strings);

    strings.insert(strings.begin() + 3, 10, "99");
    printVectorStats(strings);

    std::cout << *strings.insert(strings.end() - 1, "Arsch") << std::endl;
    printVectorStats(strings);

    strings.clear();
    strings.insert(strings.end(), 27, "88");
    printVectorStats(strings);

    strings.insert(strings.begin(), s.begin(), s.end());
    printVectorStats(strings);

    assert(strings.erase(strings.begin(), strings.end()) == strings.end());
    printVectorStats(strings);

    std::cout << "\033[34;1m" << "std::vector" << "\033[0m" << std::endl << std::endl;

    std::vector<std::string> stdStrings(5);

    stdStrings.clear();
    stdStrings.push_back("Hi");
    stdStrings.push_back("test");
    stdStrings.push_back("count the strings");
    stdStrings.push_back("Some arsches");
    printVectorStats(stdStrings);

    std::cout << *stdStrings.erase(stdStrings.begin() + 1) << std::endl;
    printVectorStats(stdStrings);

    stdStrings.pop_back();
    printVectorStats(stdStrings);

    std::cout << *stdStrings.erase(std::find(stdStrings.begin(), stdStrings.end(), "Hi")) << std::endl;
    printVectorStats(stdStrings);

    stdStrings.erase(stdStrings.begin());
    printVectorStats(stdStrings);

    stdStrings.insert(stdStrings.begin(), "A");
    printVectorStats(stdStrings);
    stdStrings.insert(stdStrings.begin(), "B");
    printVectorStats(stdStrings);
    stdStrings.insert(stdStrings.begin() + 1, "C");
    printVectorStats(stdStrings);

    stdStrings.insert(stdStrings.begin() + 3, 10, "99");
    printVectorStats(stdStrings);

    std::cout << *stdStrings.insert(stdStrings.end() - 1, "Arsch") << std::endl;
    printVectorStats(stdStrings);

    stdStrings.clear();
    stdStrings.insert(stdStrings.begin(), 27, "88");
    printVectorStats(stdStrings);

    stdStrings.insert(stdStrings.begin(), s.begin(), s.end());
    printVectorStats(stdStrings);

    assert(stdStrings.erase(stdStrings.begin(), stdStrings.end()) == stdStrings.end());
    printVectorStats(stdStrings);
}
