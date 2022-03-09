#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include "containers.hpp"

namespace ft{

template < typename T, typename A = std::allocator<T> >
class vector{
    
    public:
     
        typedef T value_type;
        typedef A allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
		//NEXT LINE SHOULD USE DIFFERENCE TYPE TO DEFINE ITSELF
		typedef size_t										size_type;
		//DIFFERENCE_TYPE IS BASED ON ITERATOR_TRAITS, CODE IT PLEASE
        /* THERE IS MORE TO ADD HERE
        ...
        */

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
				_realloc(n);
		};
	
		void resize (size_type n, value_type val = value_type()){
			if ( n < _size)
			{
				for (n = n - 1; n != _size; n++)
					_allocker.destroy(&_vector[n]);
			}
			else if (n > _size)
			{
				if (n > _capacity)
					_realloc(n);
				for (_size = _size - 1; _size != _capacity; _size++)
					_allocker.construct(&_vector[_size], val);
			}
			else 
				return ;
		};

	private:

		void _destroy_vector( void ){
			for (size_type i = 0; i != _size; i++)
				_allocker.destroy(&_vector[i]);
			_allocker.deallocate(_vector, _capacity);
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
		size_type		capacity( void ) const { return _capacity; };
		size_type		size( void ) const { return _size; };
		bool			empty( void ) const { return ((_size == 0) ? true : false); };
		size_type 		max_size() const { return _allocker.max_size(); };
		allocator_type	get_allocator( void ) const { return _allocker; };
};


}

#endif