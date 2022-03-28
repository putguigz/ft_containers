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
	
	pair_type	pair = std::make_pair(25, 0);

	ft::BST<pair_type, compare>	first(pair);


	first.insert(std::make_pair(30, 0));
	first.insert(std::make_pair(15, 0));
	first.insert(std::make_pair(17, 0));
	first.insert(std::make_pair(10, 0));
	first.insert(std::make_pair(18, 0));
	first.insert(std::make_pair(16, 0));
	first.insert(std::make_pair(35, 0));
	first.insert(std::make_pair(42, 0));
	first.insert(std::make_pair(28, 0));
	first.insert(std::make_pair(17, 0));


	print2D< ft::BST<pair_type, compare > *>(&first);

}