#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include "vector.hpp"

typedef ft::vector<int>::iterator iterator;

int main(void)
{
	ft::vector<int> v;

	for (int i = 0; i != 10; i++)
		v.push_back(i);

	for (iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << std::endl;

	iterator it2 = v.erase(v.begin() + 5, v.end());
	std::cout << "it2 = " << *it2 << std::endl;


	for (iterator it = v.begin(); it != v.end(); it++)
		std::cout << "\033[33m" << *it << std::endl;
}