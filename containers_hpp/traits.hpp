#ifndef __TRAITS_HPP__
# define __TRAITS_HPP__

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

template <class map>
struct map_traits{
		typedef typename map::key_type			key_type;
		typedef typename map::mapped_type		mapped_type;
		typedef typename map::value_type		value_type;
		typedef typename map::key_compare		key_compare;
		typedef typename map::allocator_type	allocator_type;
		typedef typename map::size_type			size_type;
		typedef typename map::reference			reference;
		typedef typename map::const_reference	const_reference;
		typedef typename map::pointer			pointer;
		typedef typename map::const_pointer		const_pointer;
		typedef typename map::difference_type	difference_type;
		typedef typename map::BST_allocator_type	BST_allocator_type;
		typedef typename map::BST_pointer			BST_pointer;
};

template <class Pair>
struct pair_traits{
	typedef typename Pair::first_type	key_type;
	typedef typename Pair::second_type	value_type;
};

template<bool B, typename first, typename second>
struct conditional{
	typedef second type;
};

template < typename first, typename second >
struct conditional<true, first, second>{
	typedef first	type;
};

template < bool B, typename T = void >
struct enable_if
{
};

template <class T>
struct enable_if<true, T> 
{ 
  typedef T type; 
};

template <class T, T v>
struct integral_constant {
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T,v> type;
	operator T() { return v; }
};

typedef integral_constant<bool,false>	false_type;
typedef integral_constant<bool,true>	true_type;

template<typename T>
struct is_integral : public false_type {};

template<>
struct is_integral<bool> : public true_type {};

template<>
struct is_integral<char> : public true_type {};

template<>
struct is_integral<wchar_t> : public true_type{};

template<>
struct is_integral<signed char> : public true_type{};

template<>
struct is_integral<short int> : public true_type{};

template<>
struct is_integral<int> : public true_type{};

template<>
struct is_integral<long int> : public true_type{};

template<>
struct is_integral<unsigned char> : public true_type{};

template<>
struct is_integral<unsigned short int> : public true_type{};

template<>
struct is_integral<unsigned int> : public true_type{};

template<>
struct is_integral<unsigned long int> : public true_type{};

template <class T1, class T2>
struct pair{
	typedef T1 first_type;
	typedef T2 second_type;

	first_type first;
	second_type second;

	pair( void ) {};
	pair (const first_type& a, const second_type& b) : first(a), second(b) { };

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

}

#endif
