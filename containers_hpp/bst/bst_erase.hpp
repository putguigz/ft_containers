#ifndef __BST_ERASE_HPP__
# define __BST_ERASE_HPP__

namespace ft{

template <class bst_pointer>
bst_pointer	destroy_no_child(bst_pointer &d_ptr)
{
	destroy_pointer(d_ptr, d_ptr->allocker);
	return NULL;
}

template <class bst_pointer>
bst_pointer	destroy_mono_child( bst_pointer &d_ptr )
{
	bst_pointer save_me;
	if (d_ptr->left)
		save_me = d_ptr->left;
	else
		save_me = d_ptr->right;
	d_ptr->left = NULL;
	d_ptr->right = NULL;
	destroy_no_child(d_ptr);
	return save_me;
}

template <class bst_pointer>
bst_pointer	destroy_two_child( bst_pointer root )
{
	struct ptr_cpy{
		bst_pointer parent;
		bst_pointer	left;
		bst_pointer right;

		ptr_cpy( bst_pointer ptr ) : parent(ptr->parent), left(ptr->left), right(ptr->right) {};
	};

	static bool flag = false;
	bst_pointer	node;
	if (flag)
	{
		flag = false;
		node = root->right;
		while (node->left)
			node = node->left;
	}
	else
	{
		flag = true;
		node = root->left;
		while (node->right)
			node = node->right;
	}

	if (root->left == node)
	{
		bst_pointer new_left = node->left;
		bst_pointer new_right = root->right;
		root->right = NULL;
		root->left = NULL;
		node->left = root;
		node->right = new_right;
		root->left = new_left;
		node->parent = root->parent;
		root->parent = node;
	}
	else if (root->right == node)
	{
		bst_pointer new_right = node->right;
		bst_pointer new_left = root->left;
		root->left = NULL;
		root->right = NULL;
		node->right = root;
		node->left = new_left;
		root->right = new_right;
		node->parent = root->parent;
		root->parent = node;
	}
	else
	{
		bool left;
		if (node->parent->left && node->parent->left == node)
		{
			node->parent->left = NULL;
			left = true;
		}
		if (node->parent->right && node->parent->right == node)
		{
			node->parent->right = NULL;
			left = false;
		}

		ptr_cpy root_cpy(root);
		ptr_cpy node_cpy(node);
		node->left = root_cpy.left;
		node->right = root_cpy.right;
		node->parent = root_cpy.parent;
		root->left = node_cpy.left;
		root->right = node_cpy.right;
		root->parent = node_cpy.parent;
		if (left)
			node_cpy.parent->left = root;
		else
			node_cpy.parent->right = root;
	}

	bst_pointer root_parent = root->parent;

	if (root_parent->left == root)
		root_parent->left = destroy(root);
	else
		root_parent->right = destroy(root);	
	
	node->recursive_balancing();

	if (node != root_parent)
	{
		bst_pointer saved_parent = root_parent->parent;
		if (saved_parent->left == root_parent)
			saved_parent->left = rotate(root_parent);
		else
			saved_parent->right = rotate(root_parent);
	}
	return node;
}

template <class bst_pointer>
bst_pointer	destroy( bst_pointer &d_stroy )
{
	bst_pointer new_node;
	
	if (!d_stroy->left && !d_stroy->right)
		new_node = destroy_no_child(d_stroy);
	else if ((!d_stroy->left && d_stroy->right) || (d_stroy->left && !d_stroy->right))
		new_node = destroy_mono_child(d_stroy);
	else
		new_node = destroy_two_child(d_stroy);
	return new_node;
}

template <class bst_pointer, class Alloc>
void	destroy_pointer( bst_pointer & tmp, Alloc fct)
{
	if (tmp != NULL)
	{
		fct.destroy(tmp);
		fct.deallocate(tmp, 1);
		tmp = NULL;
	}
}

}

#endif
