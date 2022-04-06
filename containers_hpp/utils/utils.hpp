#ifndef __UTILS_HPP__
# define __UTILS_HPP__

#include "traits.hpp"

namespace ft{

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
{
	while (first1!=last1)
	{
		if (first2==last2 || *first2 < *first1) 
			return false;
		else if (*first1 < *first2)
			return true;
		++first1; 
		++first2;
	}
	return (first2 != last2);
}

template <class T1, class T2>
struct pair{
	typedef T1 first_type;
	typedef T2 second_type;

	first_type first;
	second_type second;

	pair( void ) : first(first_type()), second(second_type()){};
	pair (const first_type& a, const second_type& b) : first(a), second(b) { };
	~pair( void ) { };

	template<class U, class V> 
	pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) { };

	pair & operator=( const pair & pr)
	{
		if (this != &pr)
		{
			first = pr.first;
			second = pr.second;
		}
		return *this;
	}
};

template <class T1, class T2>
bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>
bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }
	
template <class T1, class T2>
bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second);  }

template <class T1, class T2>
bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); }

template <class T1, class T2>
bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; }

template <class T1, class T2>
bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }

template <class T1,class T2>
ft::pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( ft::pair<T1,T2>(x,y) );
}

template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};

template <class T> 
struct less : binary_function <T,T,bool> {
	bool operator() (const T& x, const T& y) const {return x<y;}
};


}

#endif
