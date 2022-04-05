#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include "containers.hpp"
# include "iterator/iterator.hpp"
# include "utils/traits.hpp"
# include "utils/utils.hpp"

namespace ft{

template < typename T, typename A = std::allocator<T> >
class vector{
    
    public:
        typedef T 																value_type;
        typedef A																allocator_type;
		typedef typename A::size_type											size_type;
		typedef	typename A::difference_type										difference_type;
        typedef typename A::pointer            									pointer;
        typedef typename A::const_pointer      									const_pointer;
        typedef typename A::reference											reference;
        typedef typename A::const_reference    									const_reference;
		typedef typename ft::RandomAccessIterator< ft::vector<T, A>, false >		iterator;
		typedef	typename ft::RandomAccessIterator< const ft::vector<T, A>, true >	const_iterator;
		typedef typename ft::reverse_iterator< iterator >						reverse_iterator;
		typedef typename ft::reverse_iterator< const_iterator >					const_reverse_iterator;
	
	public:
        //CONSTRUCTOR
        explicit vector( const allocator_type& alloc = allocator_type() ) : _allocker(alloc), _size(0), _capacity(0)
		{
			_vector = _allocker.allocate(_capacity);
		};

		explicit vector (size_type n, const value_type& val = value_type(), 
				const allocator_type& alloc = allocator_type()) : _allocker(alloc), _size(n), _capacity(n)		
		{
			_vector = _allocker.allocate(_capacity);
			for (size_type i = 0; i != _size; i++)
				_allocker.construct(&_vector[i], val);
		};

		template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type(), typename enable_if< !is_integral<InputIterator>::value >::type* = 0) : _allocker(alloc), _size(0), _capacity(0)
		{
			_vector = _allocker.allocate(_capacity);
			assign(first, last);
		}

		vector (const vector & x) : _allocker(x._allocker), _size(0), _capacity(0){
			_vector = _allocker.allocate(_capacity);
			*this = x;
		}

		//DESTRUCTOR
        ~vector( void ){
			_destroy_vector();
		};

        //PUBLIC FCT
		iterator insert(iterator position, const value_type& val)
		{
			if (_size + 1 > _capacity)
				_realloc_memorize_position((_size + 1) * 2, position);
			insert(position, 1, val);
			return (position);
		}

		void insert(iterator position, size_type n, const value_type& val)
		{
			if (_size + n > _capacity)
			{
				if (n > _size)
					_realloc_memorize_position(_size + n, position);
				else
					_realloc_memorize_position(_size * 2, position);
			}
			for (iterator it = end() - 1; it >= position; it--)
			{
				_allocker.construct(&(*(it + n)), *it);
				_allocker.destroy(&(*it));
			}
			for (iterator it = position; it != position + n; it++)
				_allocker.construct(&(*it), val);
			_size += n;
		}

		template <class InputIterator>
    	void insert(iterator position, InputIterator first, InputIterator last, typename enable_if< !is_integral<InputIterator>::value >::type* = 0)
		{
			for (; first != last; first++)
			{
				if (_size + 1 > _capacity)
					_realloc_memorize_position((_size + 1) * 2, position);
				insert(position, 1, *first);
				position++;
			}
		}

		iterator erase (iterator position){
			return (erase(position, position + 1));
		}

		iterator erase (iterator first, iterator last){
			if (first == last)
				return first;
			size_type offset = 0;
			for(; first != last; first++)
			{
				_allocker.destroy(&(*first));
				offset++;
			}
			for (iterator it = last; it != end(); it++)
			{
				_allocker.construct(&(*(it - offset)), *it);
				_allocker.destroy(&(*it));
			}
			last -= offset;
			_size -= offset;
			return (last);
		}

		template <class InputIterator>
  		void assign(InputIterator first, InputIterator last, typename enable_if< !is_integral<InputIterator>::value >::type* = 0){
			size_type	i = 0, oldsize = _size;

			for (; first != last; first++)
		  	{
				if (i < _size)
				{
				  	_allocker.destroy(&_vector[i]);
				  	_allocker.construct(&_vector[i], *first);
				}
				else
				{
					if (i < _capacity)
					  	_allocker.construct(&_vector[i], *first);
					else
					{
						_realloc((i + 1) * 2);
						_allocker.construct(&_vector[i], *first);
					}
					_size++;
				}
				i++;
			}
			_size = i;
			if (_size < oldsize)
			{
				for (i = _size; i != oldsize; i++)
					_allocker.destroy(&_vector[i]);
			}
		}

		void assign(size_type n, const value_type& val){
			if (n > _capacity)
			{
				_realloc(n * 2);
				for (size_type i = 0; i != n; i++)
					_allocker.construct(&_vector[i], val);
			}
			else
			{
				for (size_type i = 0; i != n; i++)
				{
					_allocker.destroy(&_vector[i]);
					_allocker.construct(&_vector[i], val);
				}
			}
			_size = n;
		}

		void			push_back( const value_type & val) { 
			if (_size + 1 > _capacity)
			{
				_realloc((_size + 1) * 2);
				_allocker.construct(&_vector[_size], val);
			}
			else
				_allocker.construct(&_vector[_size], val);
			_size++;
		};

		void			pop_back( void ) {
			if (_size == 0)
				return;
			_allocker.destroy(&_vector[_size - 1]);
			_size--;
		};

		void			reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("vector::reserve");
			if (n <= _capacity)
				return;
			else
				_realloc(n * 2);
		};
	
		void resize (size_type n, value_type val = value_type()){
			if (n > _capacity)
				_realloc(n * 2);
			if ( n < _size)
			{
				for (size_type i = n; i != _size; i++)
					_allocker.destroy(&_vector[i]);
				_size = n;
			}
			else if (n > _size)
			{
				for (; _size != n; _size++)
					_allocker.construct(&_vector[_size], val);
			}
			else 
				return ;
		};

		void clear( void )
		{
			for (size_type i = 0; i != _size; i++)
				_allocker.destroy(&_vector[i]);
			_size = 0;
		};

		void swap (vector& x)
		{
			pointer		tmp_vector = _vector;
			size_type	tmp_size = _size;
			size_type	tmp_cap = _capacity;

			_vector = x._vector;
			_size = x._size;
			_capacity = x._capacity;
			x._vector = tmp_vector;
			x._size = tmp_size;
			x._capacity = tmp_cap;
		};

		//ITERATOR BASED FCT
		iterator 		begin( void ) { return (iterator(_vector)); };
		iterator		end( void ) { return (iterator(&_vector[_size])); };
		
		const_iterator	begin( void ) const { return (const_iterator(_vector)); };
		const_iterator	end( void ) const { return (const_iterator(&_vector[_size])); };
		
		reverse_iterator rbegin( void ) { return reverse_iterator(end()); };
		reverse_iterator rend( void ) { return reverse_iterator(begin()); };
		
		const_reverse_iterator rbegin( void ) const { return const_reverse_iterator(end()); };
		const_reverse_iterator rend( void ) const { return const_reverse_iterator(begin()); };

	private:

		void _destroy_vector( void ){
			for (size_type i = 0; i != _size; i++)
				_allocker.destroy(&_vector[i]);
			_allocker.deallocate(_vector, _capacity);
			_capacity = 0;
			_size = 0;
		};

		void _realloc(size_type new_capacity)
		{
			pointer new_vec;

			new_vec = _allocker.allocate(new_capacity);
			for (size_type i = 0; i != _size; i++)
			{
				_allocker.construct(&new_vec[i], _vector[i]);
				_allocker.destroy(&_vector[i]);
			}
			_allocker.deallocate(_vector, _capacity);
			_capacity = new_capacity;
			_vector = new_vec;
		};

		void _realloc_memorize_position(size_type new_capacity, iterator &position)
		{
			pointer new_vec;

			new_vec = _allocker.allocate(new_capacity);
			size_type i = 0;
			for (; i != _size; i++)
			{	
				_allocker.construct(&new_vec[i], _vector[i]);
				if (position == &(_vector[i]))
					position = &new_vec[i];
				_allocker.destroy(&_vector[i]);
			}
			if (position == &(_vector[i]))
				position = &new_vec[i];
			_allocker.deallocate(_vector, _capacity);
			_capacity = new_capacity;
			_vector = new_vec;
		};

    private:
        allocator_type	_allocker;
		size_type		_size;
		size_type		_capacity;
		pointer			_vector;

	public:
		vector& 		operator= (const vector& x){
			clear();
			reserve(x._size);
			for (size_type i = 0; i != x._size; i++)
				_allocker.construct(&_vector[i], x._vector[i]);
			_size = x.size();
			return (*this);
		};
		reference		operator[] ( size_type n ) { return _vector[n]; };
		const_reference	operator[] ( size_type n ) const { return _vector[n]; };
		reference 		front( void ) { return _vector[0]; };
		const_reference	front( void ) const { return _vector[0]; };
		reference 		back( void ) { return _vector[_size - 1]; };
		const_reference back( void ) const { return _vector[_size - 1]; };
		reference 		at (size_type n){
			if (n < 0 || n >= _size)
				throw std::out_of_range("ft::vector::at");
			else
				return (_vector[n]);
		};
		const_reference at (size_type n) const{
			if (n < 0 || n >= _size)
				throw std::out_of_range("ft::vector::at");
			else
				return (_vector[n]);
		};
		size_type		capacity( void ) const { return _capacity; };
		size_type		size( void ) const { return _size; };
		bool			empty( void ) const { return ((_size == 0) ? true : false); };
		size_type 		max_size() const { return _allocker.max_size(); };
		allocator_type	get_allocator( void ) const { return _allocker; };

};

//NON-MEMBER
template <class T, class Alloc>
void swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y){
	x.swap(y);
}

template <class T, class Alloc>
bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	if (lhs.size() == rhs.size())
	{
		for(typename ft::vector<T,Alloc>::size_type i = 0; i != lhs.size(); i++)
		{
			if (lhs.at(i) != rhs.at(i))
				return false;
		}
		return true;
	}
	return false;
}

template <class T, class Alloc>
bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
	return (!(lhs > rhs));
}


template <class T, class Alloc>
bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
	return (!(lhs < rhs));
}

}

#endif
