#ifndef __STACK_HPP__
# define __STACK_HPP__

#include "vector.hpp"

namespace ft{

template< typename T, class Container=ft::vector<T> >
class stack{
	public:
		typedef Container								container_type;
		typedef typename Container::value_type			value_type;
		typedef typename Container::size_type			size_type;
		typedef typename Container::reference			reference;
		typedef typename Container::const_reference		const_reference;

	protected:
		container_type	c;

	public:
		explicit stack( const container_type& ctnr = container_type() ) : c(ctnr) {}
		~stack( void ) {}
		stack(stack const & cpy) { *this = cpy; }
		stack & operator=(stack const &rhs) { 
			if (*this != rhs)
				this->c = rhs.c;
			return *this;
		}
	
		bool				empty( void ) const { return c.empty(); }
		size_type			size( void ) const { return c.size(); }
     	reference	 		top( void ){ return c.back(); }
		const_reference		top( void ) const{ return c.back(); }
		void				push( const value_type& val) { c.push_back(val); }
		void				pop( void ) { c.pop_back(); }

	public:
		container_type const & base( void ) const { return c; }
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
