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
	
	pair_type	pair = std::make_pair(20, 0);

	ft::BST<pair_type, compare>	*first = new ft::BST<pair_type, compare>(pair);


	first->insert(std::make_pair(30, 0));
	first->insert(std::make_pair(25, 0));
	first->insert(std::make_pair(35, 0));
	first->insert(std::make_pair(22, 0));
	first->insert(std::make_pair(60, 0));


	print2D< ft::BST<pair_type, compare > *>(first);

	delete first;
}