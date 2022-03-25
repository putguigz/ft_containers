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
	
	pair_type	pair = std::make_pair(50, 0);

	ft::BST<pair_type, compare>	*first = new ft::BST<pair_type, compare>(pair);


	first->insert(std::make_pair(25, 0));
	first->insert(std::make_pair(69, 0));
	first->insert(std::make_pair(12, 0));
	first->insert(std::make_pair(13, 0));
	first->insert(std::make_pair(15, 0));
	first->insert(std::make_pair(14, 0));
	first->insert(std::make_pair(100, 0));
	first->insert(std::make_pair(76, 0));
	first->insert(std::make_pair(85, 0));
	first->insert(std::make_pair(59, 0));



	first->insert(std::make_pair(1, 0));
	first->insert(std::make_pair(-12, 0));

	print2D< ft::BST<pair_type, compare > *>(first);

	delete first;
}