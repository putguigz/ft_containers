#ifndef __BST_HPP__
# define __BST_HPP__

# include "containers.hpp"
# include "traits.hpp"
# include "tree_printer.hpp"
# include "utils.hpp"

namespace ft{

template <class pair_type, class key_compare>
struct BST
{
	typedef typename pair_traits<pair_type>::key_type					key_type;
	typedef typename pair_traits<pair_type>::value_type					value_type;
	typedef typename std::allocator< BST< pair_type, key_compare > >	allocator_type;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;

	key_compare		cmp;
	allocator_type	allocker;

	pair_type		elem;
	pointer			left;
	pointer 		right;
	pointer			parent;

	struct balance_factor{
		balance_factor( void ) : balance(0), left(0), right(0) {}
		balance_factor( balance_factor const & src) : balance(src.balance), left(src.left), right(src.right) {}
		int balance;
		int	left;
		int	right;
	};

	balance_factor depth;	

	BST( pair_type new_pair ) : elem(new_pair), left(NULL), right(NULL), parent(NULL), depth() {}
	BST( BST<pair_type, key_compare> const & src ) : elem(src.elem), left(NULL), right(NULL), parent(NULL), depth(src.depth) {
		if (src.left != NULL)
		{
			left = allocker.allocate(1);
			allocker.construct(left, *src.left);
		}
		if (src.right != NULL)
		{
			right = allocker.allocate(1);
			allocker.construct(right, *src.right);
		}
	}
	~BST( void ) {
		destroy_sub_pointers();
	}

	reference operator=( BST<pair_type, key_compare> const & src )
	{
		if (this != &src)
		{
			elem = src.elem;
			depth =  src.depth;
			destroy_sub_pointers();
			if (src.left != NULL)
			{
				left = allocker.allocate(1);
				allocker.construct(left, *src.left);
			}
			if (src.right != NULL)
			{
				right = allocker.allocate(1);
				allocker.construct(right, *src.right);
			}
		}
		return (*this);
	}

	void	destroy_pointer( pointer & tmp)
	{
		if (tmp != NULL)
		{
			allocker.destroy(tmp);
			allocker.deallocate(tmp, 1);
			tmp = NULL;
		}
	}

	void	destroy_sub_pointers( void )
	{
		destroy_pointer(this->left);
		destroy_pointer(this->right);
	}

	pointer create_leaf(pair_type const & pair)
	{
		pointer new_leaf;
		new_leaf = allocker.allocate(1);
		allocker.construct(new_leaf, BST<pair_type, key_compare>(pair));
		return new_leaf;
	}

	bool compare( pair_type const & pair ) { return cmp(pair.first, elem.first); }

	void	balance(pointer elem)
	{
		if (!elem)
			return ;
		elem->depth.left =  max_depth_under(elem->left);
		elem->depth.right =  max_depth_under(elem->right);
		elem->depth.balance = elem->depth.left - elem->depth.right;
	}

	void	recursive_balancing( void )
	{
		if (this->left)
		{
			left->parent = this;
			left->recursive_balancing();
		}
		if (this->right)
		{
			right->parent = this;
			right->recursive_balancing();
		}
		balance(this);
	}

	pointer	rotate( pointer node )
	{
		pointer new_node = node;

		if (!node)
			return NULL;
		if (node->depth.balance < -1 || node->depth.balance > 1)
		{
			if (node->depth.balance > 0)
			{
				if (node->left->depth.right == std::max(node->left->depth.left, node->left->depth.right))
					new_node = node->left_right();
				else
					new_node = node->right_right();
			}
			else
			{
				if (node->right->depth.left == std::max(node->right->depth.left, node->right->depth.right))
					new_node = node->right_left();
				else
					new_node = node->left_left();
			}
			balance(this);
		}
		return new_node;
	}

	ft::pair<pointer, bool> insert( pair_type const & pair )
	{
		ft::pair<pointer, bool> ret;
		if (compare(pair))
		{
			if (this->left != NULL)
				ret = left->insert(pair);
			else
			{
				left = create_leaf(pair);
				ret.first = left;
				ret.second = true;
			}
		}
		else
		{
			if (pair.first == this->elem.first)
				return (ft::make_pair(this, false));
			if (this->right != NULL)
				ret = right->insert(pair);
			else
			{
				right = create_leaf(pair);
				ret.first = right;
				ret.second = true;
			}
		}
		balance(this->left);
		balance(this->right);
		left = rotate(this->left);
		right = rotate(this->right);
		if (left)
			left->parent = this;
		if (right)	
			right->parent = this;
		return ret;
	}

	pointer	copy_this( void )
	{
		pointer tmp;
		tmp = allocker.allocate(1);
		allocker.construct(tmp, this);
		return tmp;
	}

	pointer	right_right( void ){
		pointer new_start = this->left;
		this->left = new_start->right;
		new_start->right = this;
		new_start->recursive_balancing();
		return new_start;
	}

	pointer left_left(void)
	{
		pointer new_start = this->right;
		this->right = new_start->left;
		new_start->left = this;
		new_start->recursive_balancing();
		return new_start;
	}

	pointer left_right( void )
	{
		left = left->left_left();
		return (this->right_right());
	}

	pointer right_left( void )
	{
		right = right->right_right();
		return (this->left_left());
	}

	int	max_depth_under( pointer side ) {
		if (!side)
			return 0;
		else{
			return (std::max<int>(side->depth.left, side->depth.right) + 1);
		}
	}

	pointer	destroy_no_child(pointer d_ptr)
	{
		destroy_pointer(d_ptr);
		return NULL;
	}

	pointer	destroy_mono_child( pointer d_ptr )
	{
		pointer save_me;
		if (d_ptr->left)
			save_me = d_ptr->left;
		else
			save_me = d_ptr->right;
		d_ptr->left = NULL;
		d_ptr->right = NULL;
		destroy_no_child(d_ptr);
		save_me->parent = this;
		return save_me;
	}

	pointer	destroy_two_child( pointer root )
	{
		static bool flag = false;

		pointer	future_root;
		if (flag)
		{
			flag = false;
			future_root = root->right;
			while (future_root->left)
				future_root = future_root->left;
		}
		else
		{
			flag = true;
			future_root = root->left;
			while (future_root->right)
				future_root = future_root->right;
		}

		pointer delete_parent = future_root->parent;

		if (root->left == future_root)
		{
			pointer new_left = future_root->left;
			pointer new_right = root->right;
			root->right = NULL;
			future_root->left = NULL;
			future_root->left = root;
			future_root->right = new_right;
			root->left = new_left;
		}
		else if(root->right == future_root)
		{
			pointer new_right = future_root->right;
			pointer new_left = root->left;
			root->left = NULL;
			future_root->right = NULL;
			future_root->right = root;
			future_root->left = new_left;
			root->right = new_right;
		}
		else
		{	
			pointer tmp;
			pointer parent2 = future_root->parent;
			if (future_root->parent->left == future_root)
			{
				future_root->parent->left = NULL;
				tmp = future_root->parent->left;
			} 
			else
			{
				future_root->parent->right = NULL;
				tmp = future_root->parent->right;
			}
			pointer root_left = root->left;
			pointer root_right = root->right;

			pointer node_left = future_root->left;
			pointer node_right = future_root->right;
			root->left = node_left;
			root->right = node_right;
			root->parent = parent2;
			future_root->left = root_left;
			future_root->right = root_right;
			tmp = root;
		}

		if (!root->left && !root->right)
		{
			if (root->parent->left && root->parent->left == root)
				root->parent->left = destroy_no_child(root);
			else if (root->parent->right)
				root->parent->right = destroy_no_child(root);
		}
		else
		{
			if (root->parent->left && root->parent->left == root)
				root->parent->left = destroy_mono_child(root);
			else
				root->parent->right = destroy_mono_child(root);
		}

		delete_parent->recursive_balancing();
		delete_parent = rotate(delete_parent);

		return future_root;
	}


	pointer	destroy( pointer d_stroy )
	{
		pointer new_node;
	
		if (!d_stroy->left && !d_stroy->right)
			new_node = destroy_no_child(d_stroy);
		else if ((!d_stroy->left && d_stroy->right) || (d_stroy->left && !d_stroy->right))
			new_node = destroy_mono_child(d_stroy);
		else
			new_node = destroy_two_child(d_stroy);
		return new_node;
	}

	int	erase_elem( key_type key)
	{
		int ret = 0;
		if (cmp(key, this->elem.first))
		{
			if (left)
			{
				if (key == left->elem.first)
				{
					left = destroy(left);
					balance(left);
					left = rotate(left);
					ret = 1;
				}
				else
					ret = left->erase_elem(key);

			}
		}
		else
		{
			if (right)
			{
				if (key == right->elem.first)
				{	
					right = destroy(right);
					balance(right);
					right = rotate(right);
					ret = 1;
				}
				else
					ret = right->erase_elem(key);
			}
		}
		if (ret)
		{
			balance(this->left);
			balance(this->right);
			left = rotate(this->left);
			right = rotate(this->right);
			if (left)
				left->parent = this;
			if (right)	
				right->parent = this;
		}
		return ret;
	}

};

}

#endif
