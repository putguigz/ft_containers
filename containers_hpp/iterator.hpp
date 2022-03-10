#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include "vector.hpp"

namespace ft{

template < typename T>
class iterator_traits{
	public:
		typedef	T								value_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;
};

template < typename T >
class bidir_iterator : public iterator_traits<T>
{
	public:
		using typename iterator_traits<T>::value_type;
		using typename iterator_traits<T>::pointer;
		using typename iterator_traits<T>::reference;
		using typename iterator_traits<T>::difference_type;
		using typename iterator_traits<T>::iterator_category;

	public:
		bidir_iterator( void ) : _it(NULL) {};
		~bidir_iterator( void ) {};
		bidir_iterator ( bidir_iterator const & src){
				*this = src;
		};
		bidir_iterator & operator=(bidir_iterator const & src){
			if (*this != src)
				_it = src._it;
			return *this;
		};

	public:
		bool 		operator==(bidir_iterator const & src) { return (_it == src._it ? true : false); };
		bool 		operator!=(bidir_iterator const & src) { return (!(*this == src)); };
		reference 	operator*( void ) { return (*_it); };
		pointer		operator->( void ) { return (_it); };
		pointer &	operator++( void ) { return (_it++); };
		pointer		operator++( int ) { pointer tmp = _it; _it++; return tmp; };
		pointer	&	operator--( void ) { return (_it--); };
		pointer		operator--( int ) { pointer tmp = _it; _it--; return tmp; };

	protected:
		pointer _it;
};



}

#endif