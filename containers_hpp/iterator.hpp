#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include "vector.hpp"

namespace ft{

template < class Iterator >
struct iterator_traits{
		typedef	typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer           	pointer;
        typedef typename Iterator::const_pointer     	const_pointer;
        typedef typename Iterator::reference         	reference;
        typedef typename Iterator::const_reference   	const_reference;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
};

template < typename container, bool isConst = false >
class bidir_iterator
{
	public:
		typedef	typename container::value_type			value_type;
		typedef typename container::difference_type		difference_type;
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef typename std::conditional< isConst, typename container::const_reference, typename container::reference >::type	reference;
		typedef typename std::conditional< isConst, typename container::const_pointer, typename container::pointer >::type		pointer;

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

template < typename container, bool isConst = false >
class RandomAccessIterator : public bidir_iterator< container, isConst >
{
	public:
		typedef bidir_iterator< container, isConst >			bidir_iterator;

		using typename bidir_iterator::value_type;
		using typename bidir_iterator::pointer;
		using typename bidir_iterator::reference;
		using typename bidir_iterator::difference_type;
		typedef std::random_access_iterator_tag		iterator_category;

		RandomAccessIterator( void ) : bidir_iterator() {};
		RandomAccessIterator( pointer vct ) : bidir_iterator(vct) {};
		~RandomAccessIterator( void ) {};

		operator RandomAccessIterator<container, true>() const { return RandomAccessIterator<container, true>(this->_it); };

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


template < typename iterator >
class reverse_iterator{	

	typedef typename iterator::value_type	value_type;
	typedef typename iterator::pointer		pointer;
	typedef typename iterator::reference	reference;
	typedef typename iterator::difference_type	difference_type;

	private:
		iterator _it;
	public:
		reverse_iterator( void ) {};
		explicit reverse_iterator(iterator it) : _it(it) {};
		reverse_iterator( reverse_iterator<iterator> const & cpy)
		{
			*this = cpy;
		}

		operator reverse_iterator< iterator >() const { return reverse_iterator<iterator>(_it); }

		reverse_iterator & operator=( reverse_iterator<iterator> const & cpy)
		{
			if (*this != cpy)
				_it = cpy._it;
			return *this;
		}
		
		bool	operator==(reverse_iterator const & src) { return (_it == src._it ? true : false); };
		bool	operator!=(reverse_iterator const & src) { return (!(*this == src)); };

		reference operator*( void ) const{
			return (*(_it - 1));
		}

	public:
		iterator base( void ) const {return _it;};

};

}

#endif
