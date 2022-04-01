#ifndef __BST_HPP__
# define __BST_HPP__

# include "containers.hpp"
# include "traits.hpp"
# include "tree_printer.hpp"
# include "utils.hpp"
# include "bst_utils.hpp"
# include "bst_erase.hpp"

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
	typedef typename allocator_type::difference_type					difference_type;

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

	void	destroy_sub_pointers( void )
	{
		destroy_pointer(this->left, allocker);
		destroy_pointer(this->right, allocker);
	}

	pointer create_leaf(pair_type const & pair)
	{
		pointer new_leaf;
		new_leaf = allocker.allocate(1);
		allocker.construct(new_leaf, BST<pair_type, key_compare>(pair));
		return new_leaf;
	}

	bool compare( pair_type const & pair ) { return cmp(pair.first, elem.first); }

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
		allocker.construct(tmp, *this);
		return tmp;
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

	pointer	find_start( void )
	{
		if (this->left)
			return (left->find_start());
		else
			return this;
	}

	pointer	find_end( void )
	{
		if (this->right)
			return (right->find_end());
		else
			return (this + 1);
	}

	pointer find_by_key( key_type const & key )
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

	pointer find_equal(key_type const & key)
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
};

}

#endif
