#ifndef __BST_UTILS_HPP__
# define __BST_UTILS_HPP__

namespace ft{

template <class bst_pointer>
bst_pointer	right_right( bst_pointer node ){
	bst_pointer new_start = node->left;
	node->left = new_start->right;
	new_start->right = node;
	new_start->recursive_balancing();
	return new_start;
}

template <class bst_pointer>
bst_pointer left_left( bst_pointer node)
{
	bst_pointer new_start = node->right;
	node->right = new_start->left;
	new_start->left = node;
	new_start->recursive_balancing();
	return new_start;
}

template <class bst_pointer>
bst_pointer left_right( bst_pointer node )
{
	node->left = left_left(node->left);
	return (right_right(node));
}

template <class bst_pointer>
bst_pointer right_left( bst_pointer node )
{
	node->right = right_right(node->right);
	return (left_left(node));
}

template <class bst_pointer>
int	max_depth_under( bst_pointer side ) {
	if (!side)
		return 0;
	else{
		return (std::max<int>(side->depth.left, side->depth.right) + 1);
	}
}

template <class bst_pointer>
void	balance(bst_pointer elem)
{
	if (!elem)
		return ;
	elem->depth.left =  max_depth_under(elem->left);
	elem->depth.right =  max_depth_under(elem->right);
	elem->depth.balance = elem->depth.left - elem->depth.right;
}

template <class bst_pointer>
bst_pointer	rotate( bst_pointer node )
{
	bst_pointer new_node = node;

	if (!node)
		return NULL;
	if (node->depth.balance < -1 || node->depth.balance > 1)
	{
		if (node->depth.balance > 0)
		{
			if (node->left->depth.right == std::max(node->left->depth.left, node->left->depth.right))
				new_node = left_right(node);
			else
				new_node = right_right(node);
		}
		else
		{
			if (node->right->depth.left == std::max(node->right->depth.left, node->right->depth.right))
				new_node = right_left(node);
			else
				new_node = left_left(node);
		}
		balance(node);
	}
	return new_node;
}

}

#endif
