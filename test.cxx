#include <iostream>
//#include <vector>
#include "include/vector.hpp"

int main() {
	ft::vector<std::string> v;
	std::cout << std::hex
			  << v.capacity() << std::endl
			  << v.size()     << std::endl
			  << &(*v.begin())    << std::endl
			  << &(*v.end())      <<std::endl;

	v.push_back("Hi!");
	v.push_back("Hi!1");
	v.push_back("Hi!2");

	std::cout << v.capacity() << std::endl
			  << v.size()     << std::endl
			  << &(*v.begin())    << std::endl
			  << &(*v.end())     <<std::endl;
}
