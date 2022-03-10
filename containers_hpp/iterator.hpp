#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include "vector.hpp"

namespace ft{


//SHOULD BE A FUNCTION NOT A CLASS
template < typename T>
class iterator_traits{
	public:
		typedef	T								value_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;
};

template < typename T, typename A >
class bidir_iterator
{
	public:
		typedef	T								value_type;
		typedef typename A::pointer            	pointer;
		typedef typename A::reference          	reference;
		typedef std::ptrdiff_t					difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;

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