#ifndef __BST_HPP__
# define __BST_HPP__

# include "containers.hpp"

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
	BST( BST<pair_type, key_compare> const & src ) : elem(src.elem), depth(src.depth) {
		left = copy_this(*src.left);
		right = copy_this(*src.right);
	}
	~BST( void ) {
		destroy_sub_pointers();
	}

	reference operator=( BST<pair_type, key_compare> const & src )
	{
		if (this != &src)
		{
			elem = src.elem;
			destroy_sub_pointers();
			depth =  src.depth;
			left = copy_this(*src.left);
			right = copy_this(*src.right);
		}
		return (*this);
	}

	void	destroy_sub_pointers( void )
	{
		if (left != NULL)
		{
			allocker.destroy(left);
			allocker.deallocate(left, 1);
		}
		if (right != NULL)
		{
			allocker.destroy(right);
			allocker.deallocate(right, 1);
		}
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
			left_left();
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

		// std::cout << "tmp->elem.first " << tmp->elem.first << std::endl;
		// std::cout << "tmp->depth.balance " << tmp->depth.balance << std::endl;


		*this = *this->left;
		this->right = tmp;
	}

};

}

#endif
