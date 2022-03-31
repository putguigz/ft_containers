#ifndef __MAP_ITERATOR_HPP__
# define __MAP_ITERATOR_HPP__

# include "iterator.hpp"

namespace ft{

template < class map, bool isConst = false >
class MapIterator
{
	public :
		typedef typename map_traits<map>::key_type				key_type;
		typedef typename map_traits<map>::mapped_type			mapped_type;
		typedef typename map_traits<map>::value_type			value_type;
		typedef typename map_traits<map>::key_compare			key_compare;
		typedef typename map_traits<map>::allocator_type		allocator_type;
		typedef typename map_traits<map>::size_type				size_type;
		typedef typename map_traits<map>::reference				reference;
		typedef typename map_traits<map>::const_reference		const_reference;
		typedef typename map_traits<map>::pointer				pointer;
		typedef typename map_traits<map>::const_pointer			const_pointer;
		typedef typename map_traits<map>::difference_type		difference_type;
		typedef typename map_traits<map>::BST_allocator_type	BST_allocator_type;
		typedef typename map_traits<map>::BST_pointer			BST_pointer;

	public:
		MapIterator( void ) : _it(NULL) {};
		MapIterator( BST_pointer root) : _it(root) {};
		virtual ~MapIterator( void ) {};
		MapIterator( MapIterator const & src) : _it(NULL) {*this = src;};
		MapIterator & operator=( MapIterator const & src ) {
			if (*this != src)
				_it = src._it;
			return *this;
		};

		operator MapIterator< const map, true>() const { return MapIterator< const map, true>(_it); };
	
		friend bool	operator==(MapIterator const & lhs, MapIterator const & rhs){
			return (lhs.base() == rhs.base() ? true : false);
		}

		friend bool	operator!=(MapIterator const & lhs, MapIterator const & rhs){
			return (!(lhs == rhs));
		}
		reference 		operator*( void ) { return (this->_it->elem); };
		pointer			operator->( void ) { return (&(this->_it->elem)); };
		MapIterator& 	operator++( void ) {
			BST_pointer tmp_it = this->_it;
			
			if (this->_it->right)
			{
				tmp_it = tmp_it->right;
				while (tmp_it->left)
				{
					tmp_it = tmp_it->left;
				}
				_it = tmp_it;
			}
			else
			{
				tmp_it = tmp_it->parent;
				while (tmp_it)
				{
					if (!comp(tmp_it->elem.first, _it->elem.first))
						break;
					tmp_it = tmp_it->parent;
				}
				if (tmp_it)
					this->_it = tmp_it;
				else
					this->_it += 1;
			}
			return (*this); 
		};
		MapIterator		operator++( int ) { 
			MapIterator tmp(_it); operator++(); return tmp; 
		};
		MapIterator&	operator--( void ) { 
			this->_it--; return (*this); 
		};
		MapIterator		operator--( int ) { 
			MapIterator tmp(_it); operator--(); return tmp;
		};



	private:
		BST_pointer _it;
		key_compare comp;

	public:
		BST_pointer	base( void ) const { return _it;};
};

}

#endif

