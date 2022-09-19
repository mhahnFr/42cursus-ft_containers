#include "vector.hpp"
#include <iostream>
#include <iomanip>

int main() {
	ft::vector<int> a;

	ft::vector<int>::const_reverse_iterator end = a.rend();
	ft::vector<int>::reverse_iterator     begin = a.rbegin();

	std::cout << std::boolalpha << (begin == end) << std::endl;
	std::cout << (end - begin) << std::endl;
}
