#ifndef __STACK_HPP__
# define __STACK_HPP__

#include "vector.hpp"

namespace ft{

template< typename T, class Container=ft::vector<T> >
class stack{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;
	
	protected:
		container_type	_u;

	public:
		explicit stack( const container_type& ctnr = container_type() ) : _u(ctnr) {}
		~stack( void ) {}
		stack(stack const & cpy) { *this = cpy; }
		stack & operator=(stack const &rhs) { 
			if (*this != rhs)
				this->_u = rhs._u;
			return *this;
		}
	
		bool				empty( void ) const { return _u.empty(); }
		size_type			size( void ) const { return _u.size(); }
     	value_type& 		top( void ){ return _u.back(); }
		const value_type&	top( void ) const{ return _u.back(); }
		void				push( const value_type& val) { _u.push_back(val); }
		void				pop( void ) { _u.pop_back(); }
	
	public:
		container_type const & base( void ) const { return _u; }
};

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){ return lhs.base() == rhs.base(); }

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){ return !(lhs == rhs); }

template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.base() < rhs.base(); }

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.base() <= rhs.base(); }

template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return rhs < lhs; }

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return rhs <= lhs; }

}


#endif