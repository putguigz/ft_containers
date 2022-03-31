#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include "map.hpp"
#include <map>

# define PREFIX ft

int main(void)
{	
	PREFIX::map<int, int> first;


	first.insert(PREFIX::make_pair(30, 0));
	first.insert(PREFIX::make_pair(15, 0));
	first.insert(PREFIX::make_pair(17, 0));
	first.insert(PREFIX::make_pair(10, 0));
	first.insert(PREFIX::make_pair(18, 0));
	first.insert(PREFIX::make_pair(16, 0));
	first.insert(PREFIX::make_pair(35, 0));
	first.insert(PREFIX::make_pair(42, 0));
	first.insert(PREFIX::make_pair(40, 0));
	first.insert(PREFIX::make_pair(28, 0));
	first.insert(PREFIX::make_pair(20, 0));
	first.insert(PREFIX::make_pair(43, 0));
	first.insert(PREFIX::make_pair(7, 0));
	first.insert(PREFIX::make_pair(8, 0));

	//print2D(first.getBST());

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

	PREFIX::map<int, int>::iterator it = first.begin();
	PREFIX::map<int, int>::iterator it_end = first.end();
	for (; it != it_end; it++)
	{
		std::cout << it->first << std::endl;
	}
	it++;
	it++;
	it--;
	it--;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	it--;
	std::cout << it->first << std::endl;
	for (; it != first.begin(); it--);
	std::cout << it->first << std::endl;
	it--;
	for (int i= 0; i != 1000; i++)
		it++;
}