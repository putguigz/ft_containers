#include "bst.hpp"
#include <utility>
#include <functional>
#include <iostream>
#include <string>

int main(void)
{
	typedef int					Key;
	typedef std::pair<int, int>		pair_type;
	typedef std::less< Key >	compare;
	
	pair_type	pair = std::make_pair(1, 69);

	ft::BST<pair_type, compare>	*first = new ft::BST<pair_type, compare>(pair);
	ft::BST<pair_type, compare> *second;

	std::cout << first->elem.first << std::endl;
	std::cout << first->elem.second << std::endl;

	first->insert(std::make_pair(2, 18));
	first->insert(std::make_pair(0, -42));
	
	second = first->left;
	std::cout << second->elem.first << std::endl;
	std::cout << second->elem.second << std::endl;

	first = first->right;
	std::cout << first->elem.first << std::endl;
	std::cout << first->elem.second << std::endl;
}