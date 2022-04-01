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
		typedef typename map_traits<map>::difference_type		difference_type;
		typedef typename map_traits<map>::BST_allocator_type	BST_allocator_type;
		typedef typename map_traits<map>::BST_pointer			BST_pointer;
		typedef typename ft::conditional< isConst, typename map_traits<map>::const_reference, typename map_traits<map>::reference >::type	reference;
		typedef typename ft::conditional< isConst, typename map_traits<map>::const_pointer, typename map_traits<map>::pointer >::type		pointer;

	public:
		MapIterator( void ) : _it(NULL), _out(false), _offset(0) {};
		MapIterator( BST_pointer root) : _it(root), _out(false), _offset(0) {};
		virtual ~MapIterator( void ) {};
		MapIterator( MapIterator const & src) : _it(NULL), _out(false), _offset(0) {*this = src;};
		MapIterator & operator=( MapIterator const & src ) {
			if (*this != src)
			{
				_it = src._it;
				_out = src._out;
				_offset = src._offset;
			}
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
			if (_out)
			{
				_it += 1;
				this->_offset += 1;
				if (_offset == 0)
					_out = false;
			}
			else
			{
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
					{
						this->_it += 1;
						this->_offset += 1;
						this->_out = true;
					}
				}
			}
			return (*this); 
		};
		MapIterator		operator++( int ) { 
			MapIterator tmp(_it); operator++(); return tmp; 
		};
		MapIterator&	operator--( void ) { 
			if (_out)
			{
				_it -= 1;
				this->_offset -= 1;
				if (_offset == 0)
					_out = false;
			}
			else
			{
				BST_pointer tmp_it = this->_it;

				if (this->_it->left)
				{
					tmp_it = tmp_it->left;
					while (tmp_it->right)
					{
						tmp_it = tmp_it->right;
					}
					_it = tmp_it;
				}
				else
				{
					tmp_it = tmp_it->parent;
					while (tmp_it)
					{
						if (comp(tmp_it->elem.first, _it->elem.first))
							break;
						tmp_it = tmp_it->parent;
					}
					if (tmp_it)
						this->_it = tmp_it;
					else
					{
						this->_it -= 1;
						this->_offset -= 1;
						this->_out = true;
					}
				}
			}
			return (*this);
		};

		MapIterator		operator--( int ) { 
			MapIterator tmp(_it); operator--(); return tmp;
		};



	private:
		BST_pointer _it;
		key_compare comp;
		bool		_out;
		int			_offset;

	public:
		void		setOut( bool bl) { _out = bl; };
		void		setOffset( int nb) { _offset = nb; };
		BST_pointer	base( void ) const { return _it; };

};

}

#endif

