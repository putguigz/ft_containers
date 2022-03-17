#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

# include "vector.hpp"
# include "traits.hpp"

namespace ft{

template < typename container, bool isConst = false >
class bidir_iterator
{
	public:
		typedef	typename container::value_type			value_type;
		typedef typename container::difference_type		difference_type;
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef typename ft::conditional< isConst, typename container::const_reference, typename container::reference >::type	reference;
		typedef typename ft::conditional< isConst, typename container::const_pointer, typename container::pointer >::type		pointer;

	public:
		bidir_iterator( void ) : _it(NULL) {};
		bidir_iterator( pointer vct ) : _it(vct) {};
		~bidir_iterator( void ) {};
		bidir_iterator ( bidir_iterator const & src) : _it(NULL){
				*this = src;
		};

		bidir_iterator & operator=(bidir_iterator const & src){
			if (*this != src)
				_it = src._it;
			return *this;
		};

	public:
		bool 			operator==(bidir_iterator const & src) const { return (_it == src._it ? true : false); };
		bool 			operator!=(bidir_iterator const & src) const { return (!(*this == src)); };
		reference 		operator*( void ) { return (*_it); };
		pointer			operator->( void ) { return (_it); };
		bidir_iterator& operator++( void ) { _it++; return (*this); };
		bidir_iterator	operator++( int ) { bidir_iterator tmp(_it); _it++; return tmp; };
		bidir_iterator&	operator--( void ) { _it--; return (*this); };
		bidir_iterator	operator--( int ) { bidir_iterator tmp(_it); _it--; return tmp; };

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
		RandomAccessIterator ( RandomAccessIterator const & src) : bidir_iterator(){
				*this = src;
		};

		RandomAccessIterator & operator=(RandomAccessIterator const & src){
			if (*this != src)
				bidir_iterator::_it = src._it;
			return *this;
		};

		operator RandomAccessIterator<container, true>() const { return RandomAccessIterator<container, true>(this->_it); };

		//surcharge de fonctions existantes dans BIDIR:
		RandomAccessIterator& 	operator++( void ) { bidir_iterator::_it++; return (*this); };
		RandomAccessIterator	operator++( int ) { RandomAccessIterator tmp(bidir_iterator::_it); bidir_iterator::_it++; return tmp; };
		RandomAccessIterator&	operator--( void ) { bidir_iterator::_it--; return (*this); };
		RandomAccessIterator	operator--( int ) { RandomAccessIterator tmp(bidir_iterator::_it); bidir_iterator::_it--; return tmp; };

		//operator overload classics
		RandomAccessIterator 		operator+(difference_type n) const { return RandomAccessIterator((bidir_iterator::_it) + n); };
		RandomAccessIterator		operator-(difference_type n) const { return RandomAccessIterator((bidir_iterator::_it) - n); };
		friend RandomAccessIterator	operator+(difference_type n, RandomAccessIterator it) { return RandomAccessIterator(n + (it._it)); };
		difference_type				operator-(RandomAccessIterator const & it) const { return ((bidir_iterator::_it - it._it)); };
		bool 						operator<(RandomAccessIterator const & it) const { return ((bidir_iterator::_it < it._it)); };
		bool 						operator>(RandomAccessIterator const & it) const { return ((bidir_iterator::_it > it._it)); };
		bool 						operator<=(RandomAccessIterator const & it) const { return ((bidir_iterator::_it <= it._it)); };
		bool 						operator>=(RandomAccessIterator const & it) const { return ((bidir_iterator::_it >= it._it)); };
		RandomAccessIterator&		operator+=(difference_type n) { bidir_iterator::_it = bidir_iterator::_it + n; return (*this); };
		RandomAccessIterator&		operator-=(difference_type n) { bidir_iterator::_it = bidir_iterator::_it - n; return (*this); };
		reference					operator[](difference_type n) { return (*(bidir_iterator::_it + n)); }
		reference					operator[](difference_type n) const { return (*(bidir_iterator::_it + n)); }
};


template < typename iterator, typename const_ite >
class reverse_iterator{	

	typedef typename iterator::value_type		value_type;
	typedef typename iterator::pointer			pointer;
	typedef typename iterator::reference		reference;
	typedef typename iterator::difference_type	difference_type;

	private:
		iterator _it;
	public:
		reverse_iterator( void ) {};
		explicit reverse_iterator(iterator it) : _it(it) {};
		reverse_iterator( reverse_iterator<iterator, const_ite> const & cpy)
		{
			*this = cpy;
		}

		operator reverse_iterator< const_ite, iterator >() const { return reverse_iterator<const_ite, iterator>(_it); }

		reverse_iterator & operator=( reverse_iterator<iterator, const_ite> const & cpy)
		{
			if (*this != cpy)
				_it = cpy._it;
			return *this;
		}
		
		//MEMBER:
		reference			operator*( void ) const { return (*(_it - 1)); };
		reverse_iterator	operator+(difference_type n) const { return reverse_iterator(_it - n); };
		reverse_iterator &	operator++( void ) { _it--; return (*this); };
		reverse_iterator	operator++( int ) { reverse_iterator tmp = *this; _it--; return tmp; };
		reverse_iterator & 	operator+= (difference_type n) { _it -= n ; return (*this);};
		reverse_iterator	operator-(difference_type n) const { return reverse_iterator(_it + n); };
		reverse_iterator &	operator--( void ) { _it++; return (*this); };
		reverse_iterator	operator--( int ) { reverse_iterator tmp = *this; _it++; return tmp; };
		reverse_iterator & 	operator-= (difference_type n) { _it += n ; return (*this);};
		pointer				operator->( void ) { return (_it); };
		reference 			operator[] (difference_type n) const {return (_it[-n - 1]); };

		//SUPPOSEDLY NONMEMBER:
		bool	operator==(reverse_iterator const & src) { return (_it == src._it ? true : false); };
		bool	operator!=(reverse_iterator const & src) { return (!(*this == src)); };
		friend reverse_iterator operator+(difference_type n, reverse_iterator it) { return reverse_iterator(n + it._it); };
		friend reverse_iterator operator-(difference_type n, reverse_iterator it) { return reverse_iterator(n + it._it); };

	public:
		iterator base( void ) const {return _it;}

};

}

#endif
