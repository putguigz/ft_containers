#include "bst.hpp"
#include "tree_printer.hpp"
#include <utility>
#include <functional>
#include <iostream>
#include <string>

int main(void)
{
	typedef int						Key;
	typedef std::pair< Key, int >	pair_type;
	typedef std::less< Key >		compare;


	pair_type	pair = std::make_pair(10, 0);

	ft::BST<pair_type, compare>	first(pair);
	ft::BST<pair_type, compare>	*ptr = &first;

	ptr->insert(std::make_pair(30, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;
	ptr->insert(std::make_pair(15, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;
	ptr->insert(std::make_pair(17, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;
	ptr->insert(std::make_pair(10, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;
	ptr->insert(std::make_pair(18, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;
	ptr->insert(std::make_pair(16, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;
	ptr->insert(std::make_pair(35, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;
	ptr->insert(std::make_pair(42, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;
	ptr->insert(std::make_pair(28, 0));
	ptr->balance(ptr);
	ptr = ptr->rotate(ptr);
	ptr->parent = NULL;

	print2D< ft::BST<pair_type, compare > *>(ptr);

	std::cout << "BEFORE INFINITY" << std::endl;
	ptr->erase_elem(30);
	std::cout << "AFTER INFINITY" << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	print2D< ft::BST<pair_type, compare > *>(ptr);

}