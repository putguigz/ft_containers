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
	ft::pair<ft::map<int, int>::iterator,bool> ptr = first.insert(ft::make_pair(17, 0));
	first.insert(ft::make_pair(10, 0));
	first.insert(ft::make_pair(18, 0));
	first.insert(ft::make_pair(16, 0));
	first.insert(ft::make_pair(35, 0));
	first.insert(ft::make_pair(42, 0));
	first.insert(ft::make_pair(28, 0));
	first.insert(ft::make_pair(17, 0));
	first.insert(ft::make_pair(20, 0));


	print2D(first.getBST());

	std::cout << "ptr.first " << ptr.first->elem.first << std::endl;
	std::cout << "ptr.second " << ptr.second << std::endl;

}