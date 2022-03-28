#ifndef __BST_HPP__
# define __BST_HPP__

# include "containers.hpp"
# include "tree_printer.hpp"

namespace ft{

template <class pair_type, class key_compare>
struct BST
{
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

	struct balance_factor{
		balance_factor( void ) : balance(0), left(0), right(0) {}
		balance_factor( balance_factor const & src) : balance(src.balance), left(src.left), right(src.right) {}
		int balance;
		int	left;
		int	right;
	};

	balance_factor depth;	

	BST( pair_type new_pair ) : elem(new_pair), left(NULL), right(NULL), depth() {}
	BST( BST<pair_type, key_compare> const & src ) : elem(src.elem), left(NULL), right(NULL), depth(src.depth) {
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
			if (this->right != NULL)
				right->insert(pair);
			else
				right = create_leaf(pair);
			depth.right = max_depth_under(right);
		}
		//ACTUALIZE DEPTH_BALANCE AND IF SO --> ROTATE
		depth.balance = depth.left - depth.right;
		if (depth.balance < -1 || depth.balance > 1)
			left_right();
		else
			return;
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
		print2D(this);
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		left->left_left();
		print2D(this);
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		this->right_right();
	}

	void right_left( void )
	{
		print2D(this);
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		right->right_right();
		print2D(this);
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		this->left_left();
	}

	int	max_depth_under( pointer side) {
		if (!side)
			return 0;
		else{
			return (std::max<int>(side->depth.left, side->depth.right) + 1);
		}
	}

};

}

#endif
