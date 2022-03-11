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

template < typename container, typename rcv_pointer, typename rcv_reference >
class bidir_iterator
{
	public:
		typedef	typename container::value_type			value_type;
		typedef rcv_pointer								pointer;
		typedef rcv_reference							reference;
		typedef typename container::difference_type		difference_type;
		typedef std::bidirectional_iterator_tag			iterator_category;

	public:
		bidir_iterator( void ) : _it(NULL) {};
		bidir_iterator( pointer vct ) : _it(vct) {};
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

template < typename container, typename rcv_pointer, typename rcv_reference >
class RandomAccessIterator : public bidir_iterator< container, rcv_pointer, rcv_reference >
{
	public:
		typedef bidir_iterator< container, rcv_pointer, rcv_reference >			bidir_iterator;

		using typename bidir_iterator::value_type;
		using typename bidir_iterator::pointer;
		using typename bidir_iterator::reference;
		using typename bidir_iterator::difference_type;
		typedef std::random_access_iterator_tag		iterator_category;

		RandomAccessIterator( void ) : bidir_iterator() {};
		RandomAccessIterator( pointer vct ) : bidir_iterator(vct) {};
		~RandomAccessIterator( void ) {};

		RandomAccessIterator 		operator+(int n) { return RandomAccessIterator((bidir_iterator::_it) + n); };
		RandomAccessIterator		operator-(int n) { return RandomAccessIterator((bidir_iterator::_it) - n); };
		friend RandomAccessIterator	operator+(int n, RandomAccessIterator it) { return RandomAccessIterator(n + (it._it)); };
		difference_type				operator-(RandomAccessIterator it) { return ((bidir_iterator::_it - it._it)); };
		bool 						operator<(RandomAccessIterator it) { return ((bidir_iterator::_it < it._it)); };
		bool 						operator>(RandomAccessIterator it) { return ((bidir_iterator::_it > it._it)); };
		bool 						operator<=(RandomAccessIterator it) { return ((bidir_iterator::_it <= it._it)); };
		bool 						operator>=(RandomAccessIterator it) { return ((bidir_iterator::_it >= it._it)); };
		RandomAccessIterator&		operator+=(int n) { bidir_iterator::_it = bidir_iterator::_it + n; return (*this); };
		RandomAccessIterator&		operator-=(int n) { bidir_iterator::_it = bidir_iterator::_it - n; return (*this); };
		reference					operator[](int n) { return (*(bidir_iterator::_it + n)); }
};


}

#endif