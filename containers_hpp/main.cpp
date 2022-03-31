#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include "map.hpp"

int main(void)
{	
	ft::map<int, int> first;


	first.insert(ft::make_pair(30, 0));
	first.insert(ft::make_pair(15, 0));
	first.insert(ft::make_pair(17, 0));
	first.insert(ft::make_pair(10, 0));
	first.insert(ft::make_pair(18, 0));
	first.insert(ft::make_pair(16, 0));
	first.insert(ft::make_pair(35, 0));
	first.insert(ft::make_pair(42, 0));
	first.insert(ft::make_pair(40, 0));
	first.insert(ft::make_pair(28, 0));
	first.insert(ft::make_pair(20, 0));
	first.insert(ft::make_pair(43, 0));
	first.insert(ft::make_pair(7, 0));
	first.insert(ft::make_pair(8, 0));

	print2D(first.getBST());

	// first.erase(40);
	// first.erase(43);
	// first.erase(10);
	// first.erase(8);
	// first.erase(15);
	// first.erase(16);
	// first.erase(28);
	// first.erase(20);
	// first.erase(18);
	// first.erase(42);
	// first.erase(35);
	// first.erase(30);
	// first.erase(17);
	// first.erase(42);
	// first.erase(7);
	// first.erase(42);
//	print2D(first.getBST());

	ft::map<int, int>::iterator it = first.begin();
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;
	it++;
	std::cout << (*it).first << std::endl;

}