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
		MapIterator( void ) : _it(NULL), _dummy_end(NULL), _out(false), _offset(0) {};
		MapIterator( BST_pointer root, BST_pointer end, int flag) : _it(root), _dummy_end(end), _out(flag), _offset(flag) { 
			if (flag)
			{
				BST_pointer tmp = _it;
				
				_it = _dummy_end;
				_dummy_end = tmp;
			}
		};
		virtual ~MapIterator( void ) {};
		MapIterator( MapIterator const & src) : _it(NULL), _dummy_end(NULL), _out(false), _offset(0) {*this = src;};
		MapIterator & operator=( MapIterator const & src ) {
			if (this != &src)
			{
				_it = src._it;
				_dummy_end = src._dummy_end;
				_out = src._out;
				_offset = src._offset;
			}
			return *this;
		};

		operator MapIterator< const map, true>() const {
			if (_offset)
				return MapIterator< const map, true>(_dummy_end, _it, _offset);
			else
				return MapIterator< const map, true>(_it, _dummy_end, _offset);
		};
	
		friend bool	operator==(MapIterator const & lhs, MapIterator const & rhs){
			return (lhs.base() == rhs.base() ? true : false);
		}

		friend bool	operator!=(MapIterator const & lhs, MapIterator const & rhs){
			return (!(lhs == rhs));
		}
		reference 		operator*( void ) { return (this->_it->elem); };
		reference 		operator*( void ) const { return (this->_it->elem); };
		pointer			operator->( void ) { return (&(this->_it->elem)); };
		pointer			operator->( void ) const { return (&(this->_it->elem)); };
		MapIterator& 	operator++( void ) {
			if (_out)
			{
				if (this->_offset == -1)
				{
					BST_pointer tmp = _it;	
					_it = _dummy_end;
					_dummy_end = tmp;

					this->_out = false;
					this->_offset = 0;
				}
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
						BST_pointer tmp = _it;
						_it = _dummy_end;
						_dummy_end = tmp;

						this->_offset = 1;
						this->_out = true;
					}
				}
			}
			return (*this); 
		};
		MapIterator		operator++( int ) { 
			MapIterator tmp(_it, _dummy_end, _offset); operator++(); return tmp; 
		};
		MapIterator&	operator--( void ) { 
			if (_out)
			{
				if (this->_offset == 1)
				{
					BST_pointer tmp = _it;
					_it = _dummy_end;
					_dummy_end = tmp;

					this->_out = false;
					this->_offset = 0;
				}
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
						BST_pointer tmp = _it;
						_it = _dummy_end;
						_dummy_end = tmp;

						this->_out = true;
						this->_offset = -1;
					}
				}
			}
			return (*this);
		};

		MapIterator		operator--( int ) { 
			MapIterator tmp(_it, _dummy_end, _offset); operator--(); return tmp;
		};

	private:
		BST_pointer _it;
		BST_pointer	_dummy_end;
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

