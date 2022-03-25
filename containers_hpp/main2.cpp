#include "bst.hpp"
#include <utility>
#include <functional>
#include <iostream>
#include <string>

int main(void)
{
	typedef std::string				Key;
	typedef std::pair< Key, int >	pair_type;
	typedef std::less< Key >		compare;
	
	pair_type	pair = std::make_pair("Dov", 69);

	ft::BST<pair_type, compare>	*first = new ft::BST<pair_type, compare>(pair);
	ft::BST<pair_type, compare> *second;

	std::cout << first->elem.first << std::endl;
	std::cout << first->elem.second << std::endl;

	first->insert(std::make_pair("Guigz", 18));
	first->insert(std::make_pair("Philippe", 5));
	
	second = first->left;
	std::cout << second->elem.first << std::endl;
	std::cout << second->elem.second << std::endl;

	first = first->right;
	std::cout << first->elem.first << std::endl;
	std::cout << first->elem.second << std::endl;
}