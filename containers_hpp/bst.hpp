#ifndef __BST_HPP__
# define __BST_HPP__

# include "containers.hpp"
# include "traits.hpp"
# include "tree_printer.hpp"

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

	// void	balance(pointer elem)
	// {
	// 	elem->depth.left =  max_depth_under(left);
	// 	elem->depth.right =  max_depth_under(right);

	// }

	void insert( pair_type const & pair )
	{
		if (compare(pair))
		{
			if (this->left != NULL)
				left->insert(pair);
			else
				left = create_leaf(pair);
			depth.left = max_depth_under(left);
		}
		else
		{
			if (pair.first == this->elem.first)
				return;
			if (this->right != NULL)
				right->insert(pair);
			else
				right = create_leaf(pair);
			depth.right = max_depth_under(right);
		}
		if (left)
			left->parent = this;
		if (right)	
			right->parent = this;
		depth.balance = depth.left - depth.right;
		if (depth.balance < -1 || depth.balance > 1)
		{
			if (depth.balance > 0)
			{
				if (left->depth.right == std::max(left->depth.left, left->depth.right))
					left_right();
				else
					right_right();
			}
			else
			{
				if (right->depth.left == std::max(right->depth.left, right->depth.right))
					right_left();
				else
					left_left();
			}
			connect_parents();
		}
	}

	void	connect_parents( void )
	{
		if (left)
		{
			left->parent = this;
			left->connect_parents();
		}
		if (right)
		{	
			right->parent = this;
			right->connect_parents();
		}
	}

	pointer	copy_this( const_pointer cpy )
	{
		if (cpy == NULL)
			return NULL;
		pointer tmp;
		tmp = allocker.allocate(1);
		allocker.construct(tmp, *cpy);
		return tmp;
	}

	void	right_right( void ){
		pointer tmp = copy_this(this);
		pointer new_root = tmp->left;

		tmp->left = new_root->right; 

		new_root->right = tmp;

		tmp->depth.left = max_depth_under(tmp->left);
		tmp->depth.balance = tmp->depth.left - tmp->depth.right;

		*this = *new_root;

		depth.right = max_depth_under(right);
		depth.balance = depth.left - depth.right;

		destroy_pointer(new_root);
	}

	void left_left(void)
	{
		pointer tmp = copy_this(this);
		pointer new_root = tmp->right;
		tmp->right = new_root->left;

		new_root->left = tmp;

		tmp->depth.right = max_depth_under(tmp->right);
		tmp->depth.balance = tmp->depth.left - tmp->depth.right;

		*this = *new_root;

		depth.left = max_depth_under(left);
		depth.balance = depth.left - depth.right;

		destroy_pointer(new_root);
	}

	void left_right( void )
	{
		left->left_left();
		this->right_right();
	}

	void right_left( void )
	{
		right->right_right();
		this->left_left();
	}

	int	max_depth_under( pointer side) {
		if (!side)
			return 0;
		else{
			return (std::max<int>(side->depth.left, side->depth.right) + 1);
		}
	}

	pointer find_by_key( key_type key )
	{
		if (cmp(key, this->elem.first))
		{
			if (left)
				return (left->find_by_key(key));
			else
				return NULL;
		}
		else
		{
			if (key == this->elem.first)
				return this;
			else if (right)
				return (right->find_by_key(key));
			else
				return NULL;
		}
	}

	int	destroy_no_child(pointer d_ptr)
	{
		pointer parent = d_ptr->parent;
		if (!parent)
			return 0;
		else
		{
			if (d_ptr == parent->left)
			{
				destroy_pointer(parent->left);
				return 1;
			}
			else
			{
				destroy_pointer(parent->right);
				return -1;
			}
		}
	}

	void	destroy_mono_child(pointer d_ptr)
	{
		pointer parent = d_ptr->parent;
		pointer save_me;
		if (d_ptr->left)
			save_me = d_ptr->left;
		else
			save_me = d_ptr->right;
		d_ptr->left = NULL;
		d_ptr->right = NULL;
		int ret = destroy_no_child(d_ptr);
		if (ret > 0)
			parent->left = save_me;
		else if (ret < 0)
			parent->right = save_me;
		save_me->parent = parent;
	}

	void	erase_elem( key_type key )
	{
		pointer d_stroy = find_by_key(key);
		if (!d_stroy)
			return ;
		if (!d_stroy->left && !d_stroy->right)
			destroy_no_child(d_stroy);
		if ((!d_stroy->left && d_stroy->right) || (d_stroy->left && !d_stroy->right))
			destroy_mono_child(d_stroy);
	}

};

}

#endif
