#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include "containers.hpp"
# include "iterator.hpp"

namespace ft{

template < typename T, typename A = std::allocator<T> >
class vector{
    
    public:
        typedef T 														value_type;
        typedef A														allocator_type;
		typedef typename A::size_type									size_type;
		typedef	typename A::difference_type								difference_type;
        typedef typename A::pointer            							pointer;
        typedef typename A::const_pointer      							const_pointer;
        typedef typename A::reference          							reference;
        typedef typename A::const_reference    							const_reference;
		typedef typename ft::RandomAccessIterator< ft::vector<T, A>, pointer, reference >				iterator;
		typedef	typename ft::RandomAccessIterator< ft::vector<T, A>, const_pointer, const_reference >	const_iterator;

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
		/* THERE IS MORE TO ADD HERE
        **INPUT OPERATOR CONSTRUCTOR
		**COPY CONSTRUCTOR
        */


		//DESTRUCTOR
        ~vector( void ){
			_destroy_vector();
		};

        //PUBLIC FCT
		void			push_back( const value_type & val) { 
			if (_size + 1 > _capacity)
			{
				_realloc(_size + 1);
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
			std::cout << "RESERVE" << std::endl;
			if (n > max_size())
				throw std::length_error("vector::reserve");
			if (n <= _capacity)
				return;
			else
				_realloc(n);
		};
	
		void resize (size_type n, value_type val = value_type()){
			std::cout << "RESIZE" << std::endl;
			if (n > _capacity)
				_realloc(n);
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

		iterator 		begin( void ) { return (iterator(_vector)); };
		const_iterator	begin( void ) const { return (const_iterator(_vector)); };
		iterator		end( void ) { return (iterator(&_vector[_size])); };

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


    private:
        allocator_type	_allocker;
		size_type		_size;
		size_type		_capacity;
		pointer			_vector;

	public:
		reference		operator[] ( size_type n ) { return _vector[n]; };
		const_reference	operator[] ( size_type n ) const { return _vector[n]; };
		reference 		front( void ) { return _vector[0]; };
		const_reference	front( void ) const { return _vector[0]; };
		reference 		back( void ) { return _vector[_size - 1]; };
		const_reference back( void ) const { return _vector[_size - 1]; };
		reference 		at (size_type n){
			if (n < 0 && n >= _size)
				throw std::out_of_range("ft::vector::at");
			else
				return (_vector[n]);
		};
		const_reference at (size_type n) const{
			if (n < 0 && n >= _size)
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


}

#endif