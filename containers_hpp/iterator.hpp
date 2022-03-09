#ifndef __ITERATOR_HPP__
# define __ITERATOR_HPP__

namespace ft{

template < typename T>
class iterator_traits{
	public:
		typedef	T			value_type;
		typedef	T*			pointer;
		typedef	T&			reference;
		typedef ptrdiff_t	difference_type;
		typedef std::bidirectional_iterator_tag	iterator_category;
};

template < typename T>
class bidir_iterator : public iterator_traits<T>
{
	public:
		bidir_iterator( void ) : _it(nullptr) { };
		~bidir_iterator( void ) {};
		bidir_iterator ( bidir_iterator const & src){
			if (*this == src)
				return;
			else
				it = src;
		};
		bidir_iterator & operator=(bidir_iterator const & src){
			_it = src._it;
		};

	public:
		bool 		operator==(bidir_iterator const & src) { return (_it = src._it ? true : false); };
		bool 		operator!=(bidir_iterator const & src) { return (!(this == src)); };
		reference 	operator*( void ) { return (*_it); };
		reference	operator->( void ) { return (*_it); };
		pointer &	operator++( void ) { return (_it += 1); };
		pointer		operator++( int ) { pointer tmp = _it; _it += 1; return tmp; };
		pointer	&	operator--( void ) { return (_it -= 1); };
		pointer		operator--( int ) { pointer tmp = _it; _it -= 1; return tmp; };
	private:
		pointer _it;
};


}

#endif