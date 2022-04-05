#ifndef __TREE_PRINTER_HPP__
# define __TREE_PRINTER_HPP__

# include "../containers.hpp"
# define COUNT 10

template<class pointer>
void print2DUtil(pointer root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout<<" ";
    std::cout<< root->elem.first << ", ";
	std::cout << RED << root->depth.balance << RESET <<", ";
	if (root->parent)
		std::cout << YELLOW << root->parent->elem.first << RESET << std::endl;
	else
		std::cout << FIRE << "NICHT" << RESET << std::endl;

 
    // Process left child
    print2DUtil(root->left, space);
}
 
template <class pointer>
void print2D(pointer root)
{
	std::cout << "\n<========================>\n";
    // Pass initial space count as 0
    print2DUtil(root, 0);
	std::cout << "\n<========================>\n";
}

#endif