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
			allocker.construct(right, *src.left);
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
			pointer tmp1 = left, tmp2 = right;
			if (src.left != NULL)
			{
				left = allocker.allocate(1);
				allocker.construct(left, *src.left);
			}
			if (src.right != NULL)
			{
				right = allocker.allocate(1);
				allocker.construct(right, *src.left);
			}
			destroy_pointer(tmp1);
			destroy_pointer(tmp2);
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
			depth.left = std::max<int>(left->depth.left, left->depth.right) + 1;

		}
		else
		{
			if (this->right != NULL)
				right->insert(pair);
			else
				right = create_leaf(pair);
			depth.right = std::max<int>(right->depth.left, right->depth.right) + 1;
		}
		//ACTUALIZE DEPTH_BALANCE AND IF SO --> ROTATE
		depth.balance = depth.left - depth.right;
		if (depth.balance < -1 || depth.balance > 1)
			right_right();
		else
			return;
	}

	pointer	copy_this( BST<pair_type, key_compare> const & cpy )
	{
		pointer tmp;
		tmp = allocker.allocate(1);
		allocker.construct(tmp, cpy);
		return tmp;
	}

	void	left_left( void ){
		pointer tmp = copy_this(*this);
		destroy_pointer(tmp->left);
		
		tmp->depth.left = 0;
		tmp->depth.balance = tmp->depth.left - tmp->depth.right;

		*this = *(this->left);
		this->right = tmp;

		depth.right = std::max<int>(right->depth.left, right->depth.right) + 1;
		depth.balance = depth.left - depth.right;
	}

	void	right_right( void ){
		pointer tmp = copy_this(*this);
		destroy_pointer(tmp->right);
		
		tmp->depth.right = 0;
		tmp->depth.balance = tmp->depth.left - tmp->depth.right;

		*this = *(this->right);
		this->left = tmp;

		depth.left = std::max<int>(left->depth.left, left->depth.right) + 1;
		depth.balance = depth.left - depth.right;
	}

};

}

#endif
