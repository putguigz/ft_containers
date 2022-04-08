#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include <iomanip>
#include <list>
#include "utils/tree_printer.hpp"

#if STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
using namespace std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
using namespace ft;
#endif

# define RED "\033[38;5;124m"
# define RESET "\033[0m"
# define BLUE "\033[38;5;63m"
# define GREEN "\033[38;5;42m"
# define FIRE "\033[38;5;166m"
# define PURPLE "\033[38;5;105m"
# define LIGHTBLUE "\033[38;5;87m"
# define YELLOW "\033[38;5;220m"
# define DEV "\033[38;5;200m"
# define ERR_NO_NUM -1
# define ERR_NO_MEM -2

template <typename T>
void printVector( vector<T> const & vec, std::string name = std::string())
{
	std::cout << "<--------  " << FIRE << "VECTOR PRINT" << RESET << "   ---------->" << std::endl;
	std::cout << DEV << "NAME : " << name << RESET << std::endl;
	std::cout << "SIZE : ";
	std::cout << std::setw(10) << vec.size() << std::endl;
	
	if (vec.size() > 0)
	{
		std::cout << "CONTENT : ";
		typename vector<T>::const_iterator it = vec.begin();
		for (; it != vec.end(); it++)
			std::cout << *it << " ";
		std::cout << std::endl;
	}
	std::cout << "<--------  " << YELLOW << "END OF PRINT" << RESET << "   ---------->" << std::endl << std::endl;
}

int main(void)
{
#if STD //CREATE A REAL STL EXAMPLE
	std::cout << RED << "STD" << RESET << std::endl;
using namespace std;
#else
	std::cout << BLUE << "FT" << RESET << std::endl;
using namespace ft;
#endif

	typedef vector<int>::iterator 			iterator;
	typedef vector<int>::reverse_iterator	reverse_iterator;

	{
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*              VECTOR_CONSTRUCTORS_DESTRUCTORS                *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl << std::endl;

		std::list<int> lst;
		for (int i = 0; i != 50; i++)
			lst.push_front(i + 1);

		vector<int> vi;
		vector<int> vi2(4, 100);
		vector<int> vi3(lst.begin(), lst.end());
		vector<int> vi4 = vi3;
		vector<int> vi5(vi2);

		printVector(vi, "vi");
		printVector(vi2, "vi2"); 
		printVector(vi3, "vi3");
		printVector(vi4, "vi4 (operator= vi3)");
		printVector(vi5, "vi5 (copy operator of vi2)");
	}

	{
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*                         ITERATORS                           *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl << std::endl;

		vector<int> v1;
		for (int i = 50; i != 0; i--)
			v1.push_back(i);
		
		printVector(v1, "v1");

		iterator it = v1.begin();
		--it;
		it = it - 1;
		it = it + 2;
		std::cout << *it << std::endl;
		for (;it != v1.end() - 10; it++);
		std::cout << *it << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << it[1] << std::endl;
		std::cout << ((it < it + 1) ? "true":"false") << std::endl;
		std::cout << ((it > it + 1) ? "true":"false") << std::endl;
		std::cout << ((it <= it) ? "true":"false") << std::endl;
		std::cout << ((it >= it) ? "true":"false") << std::endl;
		it -= 10;
		it += 5;
		for (;it != v1.end() - 1; it++)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*                        REVERSE_IT                           *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl << std::endl;

		vector<int> v1;
		for (int i = 0; i != 50; i++)
			v1.push_back(i + 1);
		
		printVector(v1, "v1");

		reverse_iterator r_it = v1.rbegin();
		for (; r_it != v1.rend(); r_it++)
			std::cout << *r_it << " ";
		std::cout << std::endl;
	}

	{
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*                         RESIZING                            *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl << std::endl;

		vector<int> myvector;

		std::cout << "Is Empty ? " << (myvector.empty()? "True": "False") << std::endl;
		std::cout << std::endl;

  		for (int i=1;i<10;i++) 
			myvector.push_back(i);

		printVector(myvector, "myVector Before");
  		myvector.resize(5);
		printVector(myvector, "myVector AFTER RESIZE 5");
  		myvector.resize(8,100);
		printVector(myvector, "myVector AFTER RESIZE (8, 100)");
  		myvector.resize(12);
		printVector(myvector, "myVector AFTER RESIZE 12");
		std::cout << "Is Empty ? " << (myvector.empty()? "True": "False") << std::endl;
		std::cout << std::endl;

		std::cout << "CAPACITY is " << (myvector.capacity()) << std::endl;
		myvector.reserve(100);
		std::cout << "NEW CAPACITY is " << (myvector.capacity()) << std::endl;
		
		std::cout << "MAX SIZE is" << myvector.max_size() << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*                         ACCESSORS                           *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl << std::endl;
	
		vector<int> v1;
		for (int i = 0; i != 50; i++)
			v1.push_back(i + 1);
	
		printVector(v1, "v1");
		std::cout << v1.front() << std::endl;
		int & ref = v1.front();
		ref = 5000;
		v1[49] = 42;
		std::cout << v1.back() << std::endl;
		printVector(v1, "v1 AFTER");

		try {
			v1.at(600);
		}
		catch ( const std::out_of_range e)
		{
			std::cout << e.what() << std::endl;
		}

		std::cout << v1.at(25) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*                        MODIFIERS                            *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl << std::endl;
	
		vector<int> first;
		vector<int> second;
		vector<int> third;

		first.assign (7,100);
		
		printVector(first, "first");

		vector<int>::iterator it;
		it = first.begin() + 1;

		second.assign (it,first.end() - 1);

		printVector(second, "second");

		int myints[] = {1776,7,4};
		third.assign (myints , myints+3);

		printVector(third, "third");

		third.push_back(42);
		for (int i = 99; i != 199; i++)
			third.push_back(i);
		printVector(third, "third after 101 push-backs");
		for (int i = 0; i != 10; i++)
			third.pop_back();
		printVector(third, "third after 10 pops");
		int j = third.size();
		for (int i = 0; i != j - 1; i++)
			third.pop_back();
		printVector(third, "third after EVERYTHING minus 1 pops");
		
		third.insert (third.begin() , 2 ,300);
		third.insert (third.end(), second.begin(), second.end());
		third.insert (third.end(), first.begin(), first.end());

		printVector(third, "third after INSERTIONS");
		third.erase(third.begin(), third.begin() + 2);
		printVector(third, "third after 1st ERASE");
		third.erase(third.begin());
		printVector(third, "third after 2st ERASE");
		third.erase(third.end() - 1);
		printVector(third, "third after last ERASE");

		first.resize(42, 42);
		printVector(first, "first after resize");
		third.swap(first);
		printVector(third, "third after swap");
		printVector(first, "first after swap");
		swap(first, third);
		printVector(third, "third after swap");
		printVector(first, "first after swap");
		std::cout << std::endl;
		
		std::cout << ((third == first)? "third is equal to first": "third is not equal to first") << std::endl;
		std::cout << ((third != first)? "third is not equal to first": "third is equal to first") << std::endl;
		std::cout << ((third < first)? "third is inf to first": "third is not inf to first") << std::endl;
		std::cout << ((third > first)? "third is sup to first": "third is not sup to first") << std::endl;
		std::cout << ((third <= first)? "third is inf or equal to first": "third is not inf or equal to first") << std::endl;
		std::cout << ((third >= first)? "third is sup or equal to first": "third is not sup or equal to first") << std::endl;
		std::cout << std::endl;

		first.clear();
		third.clear();
		printVector(third, "third after swap");
		printVector(first, "first after swap");
	}

	{
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*                            STACK                            *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl << std::endl;

		stack<std::string> s1;

		std::cout << "IsEmpty ? " << (s1.empty()? "True": "False") << std::endl;
		std::cout << YELLOW << "LET'S PUSH" << RESET << std::endl;
		s1.push("Nico");
		std::cout << "IsEmpty ? " << (s1.empty()? "True": "False") << std::endl;
		std::cout << "s1 top is " << s1.top() << std::endl;
		std::cout << YELLOW << "LET'S PUSH" << RESET << std::endl;
		s1.push("Guillaume");
		std::cout << "s1 top is " << s1.top() << std::endl;
		std::cout << YELLOW << "LET'S PUSH" << RESET << std::endl;
		s1.push("Pilou");
		std::cout << "s1 top is " << s1.top() << std::endl;
		std::cout << YELLOW << "LET'S PUSH" << RESET << std::endl;
		s1.push("Philippe");
		std::cout << "s1 top is " << s1.top() << std::endl;
		std::cout << YELLOW << "LET'S PUSH" << RESET << std::endl;
		s1.push("Dov");
		std::cout << "s1 top is " << s1.top() << std::endl;
		std::cout << YELLOW << "LET'S PUSH" << RESET << std::endl;
		s1.push("Theo");
		std::cout << "s1 top is " << s1.top() << std::endl;
		std::cout << YELLOW << "LET'S PUSH" << RESET << std::endl;
		s1.push("Nastou");
		std::cout << "s1 top is " << s1.top() << std::endl;
		std::cout << YELLOW << "LET'S POP" << RESET << std::endl;
		s1.pop();
		std::cout << "s1 top is " << s1.top() << std::endl;
		std::cout << "size is " << s1.size() << std::endl;
		int j = s1.size();
		for (int i = 0; i != j ; i++ )
		{
			std::cout << YELLOW << "LET'S POP" << RESET << std::endl;
			s1.pop();
		}
		std::cout << std::endl;
		std::cout << "IsEmpty ? " << (s1.empty()? "True": "False") << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;


		std::cout << "RELATIONAL OPERATOR TESTS"<< std::endl;

		s1.push("Guigz");
		s1.push("Nico");
		s1.push("Nas");


		stack<std::string> s2;
		s2.push("Guigz");
		s2.push("Nico");
		s2.push("Nas");

		std::cout << ((s1 == s2)? "s1 is equal to s2": "s1 is not equal to s2") << std::endl;
		std::cout << ((s1 != s2)? "s1 is not equal to s2": "s1 is equal to s2") << std::endl;
		std::cout << ((s1 < s2)? "s1 is inf to s2": "s1 is not inf to s2") << std::endl;
		std::cout << ((s1 > s2)? "s1 is sup to s2": "s1 is not sup to s2") << std::endl;
		std::cout << ((s1 <= s2)? "s1 is inf or equal to s2": "s1 is not inf or equal to s2") << std::endl;
		std::cout << ((s1 >= s2)? "s1 is sup or equal to s2": "s1 is not sup or equal to s2") << std::endl;

		std::cout << YELLOW << "LET'S POP in S2" << RESET << std::endl;
		s2.pop();
		std::cout << ((s1 == s2)? "s1 is equal to s2": "s1 is not equal to s2") << std::endl;
		std::cout << ((s1 != s2)? "s1 is not equal to s2": "s1 is equal to s2") << std::endl;
		std::cout << ((s1 < s2)? "s1 is inf to s2": "s1 is not inf to s2") << std::endl;
		std::cout << ((s1 > s2)? "s1 is sup to s2": "s1 is not sup to s2") << std::endl;
		std::cout << ((s1 <= s2)? "s1 is inf or equal to s2": "s1 is not inf or equal to s2") << std::endl;
		std::cout << ((s1 >= s2)? "s1 is sup or equal to s2": "s1 is not sup or equal to s2") << std::endl;
	}

	{
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*                            MAP                              *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl << std::endl;
	
		vector<int>			v1;
		map<int, int>		m1;
		std::cout << "isEmpty?" << (m1.empty()?"True":"False") << std::endl;
		for (int i = 0; i != 50; i++)
			v1.push_back(i + 1);
		std::cout << "isEmpty?" << (m1.empty()?"True":"False") << std::endl;

		srand( time( NULL ));
		for (int i  = 50; i != 0; i--)
		{
			int j = rand() % i;
			m1.insert(make_pair(v1[j], 42));
			iterator it = v1.begin() + j;
			v1.erase(it);
		}
		std::cout << "SIZE OF MAP = " << m1.size() << std::endl;;
#if !STD //CREATE A REAL STL EXAMPLE
		print2D(m1.getBST());
#endif
		m1.erase(m1.find(26));
		m1.erase(42);
		m1.erase(m1.begin(), m1.find(5));
		std::cout << "SIZE OF MAP = " << m1.size() << std::endl;;
#if !STD //CREATE A REAL STL EXAMPLE
		print2D(m1.getBST());
#endif
		std::cout << "number of 49 im map = " << m1.count(49) << std::endl;
		std::cout << DEV << "SIZE_MAX = " << m1.max_size() << RESET << std::endl;
		map<int, int>::iterator it;

		it = m1.begin();
		--(++it);
		(it++)--;
		for(; it != m1.end(); it++)
		{
			std::cout << it->first << " " << FIRE << it->second << RESET << std::endl;
			it->second += 1;
		}
		std::cout << std::endl;
		
		map<int, int>::reverse_iterator ti;
		ti = m1.rbegin();
		for(; ti != m1.rend(); ti++)
			std::cout << ti->first << " " << GREEN <<  ti->second << RESET << std::endl;
		std::cout << "SIZE OF MAP = " << m1.size() << std::endl;;
		
		std::cout << std::endl;
		
		map<int, int> m2;
		m2[43] = 52;
		m2[42] = 53;
		m2[42] = 56;
		
		m1.swap(m2);
		std::cout << RED << "M1 IS " << RESET << std::endl;
		for (it = m1.begin(); it != m1.end(); it++)
			std::cout << it->first << " " << FIRE << it->second << RESET << std::endl;
		
		std::cout << std::endl;

		std::cout << RED << "M2 IS " << RESET << std::endl;
		for (it = m2.begin(); it != m2.end(); it++)
			std::cout << it->first << " " << FIRE << it->second << RESET << std::endl;

		std::cout << "CLEARING OUT MAP" << std::endl;
		m1.clear();
	}
}
