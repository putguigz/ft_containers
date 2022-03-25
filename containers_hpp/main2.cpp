#include "bst.hpp"
#include "tree_printer.hpp"
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
	ft::BST<pair_type, compare> *second, *third;

	std::cout << first->elem.first << std::endl;
	std::cout << first->elem.second << std::endl;

	first->insert(std::make_pair("Guigz", 18));
	first->insert(std::make_pair("Philippe", 5));

	second = first->right;
	std::cout << second->elem.first << std::endl;
	std::cout << second->elem.second << std::endl;

	third = second->right;
	std::cout << third->elem.first << std::endl;
	std::cout << third->elem.second << std::endl;

	print2D< ft::BST<pair_type, compare > *>(first);

	delete first;
}