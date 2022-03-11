#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include "vector.hpp"

namespace ft{

template < class Iterator >
struct iterator_traits{
		typedef	typename Iterator::value_type			value_type;
		typedef	typename Iterator::pointer				pointer;
		typedef	typename Iterator::reference			reference;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
};

template < typename container >
class bidir_iterator
{
	public:
		typedef	typename container::value_type			value_type;
		typedef typename container::pointer       		pointer;
		typedef typename container::reference      		reference;
		typedef typename container::difference_type		difference_type;
		typedef std::bidirectional_iterator_tag			iterator_category;

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