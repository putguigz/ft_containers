#include "containers.hpp"
#include "vector.hpp"
#include <vector>

typedef struct	my_struct{
	int i;
	std::string str;
}		t_struct;

template < typename V >
void	print_vector(V & bail)
{
	std::cout << "SIZE = " << bail.size() << std::endl;
	std::cout << "CAPACITY = " << bail.capacity() << std::endl;
	typename V::iterator it = bail.begin();
	typename V::iterator it_end = bail.end();
	for (; it != it_end; it++)
		std::cout << "it_elem = " << *it << std::endl;
}

int main(void)
{
	{		
		ft::vector<int> v1;
		ft::vector<int> v2;
		for (int i = 0; i != 10; i++)
			v1.push_back(i);

		for (int i = 10; i != 20; i++)
			v2.push_back(i);

		std::cout << "FT - BEFORE" << std::endl;
		print_vector(v1);
		std::cout << std::endl;
		v1.insert(v1.end(), v2.begin() + 3, v2.end());
		std::cout << "FT - AFTER" << RED << std::endl;
		print_vector(v1);
		std::cout << RESET << std::endl;
	}
	{		
		std::vector<int> v1;
		std::vector<int> v2;
		for (int i = 0; i != 10; i++)
			v1.push_back(i);

		for (int i = 10; i != 20; i++)
			v2.push_back(i);

		std::cout << YELLOW << "STD - BEFORE" << std::endl;
		print_vector(v1);
		std::cout << std::endl;
		v1.insert(v1.end(), v2.begin() + 3, v2.end());
		std::cout << "STD - AFTER" << std::endl;
		print_vector(v1);
		std::cout << RESET << std::endl;
	}
	// {
	// 	ft::vector<int> v1(20, 42);
		
	// 	ft::vector<int> v2;
	// 	for (int i = 0; i != 20; i++)
	// 		v2.push_back(i);

	// 	print_vector(v1);
	// 	v1.assign(v2.begin(), v2.end());
	// 	std::cout << std::endl;
	// 	print_vector(v1);

	// }

	// {
	// 	std::cout << std::endl;
	// 	std::vector<int> v1(20, 42);

	// 	std::vector<int> v2;
	// 	for (int i = 0; i != 20; i++)
	// 		v2.push_back(i);


	// 	std::cout << BLUE;
	// 	print_vector(v1);
	// 	v1.assign(v2.begin(), v2.end());
	// 	std::cout << std::endl;
	// 	print_vector(v1);
	// 	std::cout << RESET;
	// }
	// t_struct	elem = {4, "Hello world"};
	// typedef ft::vector<int>::iterator iterator;
	{
		// using namespace ft;
		// ft::vector<int> v1;
		// v1.push_back(0);
		// v1.push_back(1);
		// v1.push_back(2);
		// v1.push_back(3);
		// v1.push_back(4);
		// v1.push_back(5);
		// ft::vector<int>::reverse_iterator it2 = v1.rbegin();
		// std::cout << &it2 << std::endl;
		// it2++;
		// std::cout << *it2 << std::endl;
		// std::cout << it2[0] << std::endl;
		// std::cout << it2[1] << std::endl;
		// it2[1] = 42;
		// std::cout << it2[1] << std::endl;
	
		// print_vector(v1);

		// iterator it = v1.begin();
		// for (; it != v1.end(); it++)
		// {
		// 	std::cout << it->i << std::endl;
		// 	std::cout << it->str << std::endl;
		// }
	}
	// {
	// 	using namespace std;
	// 	std::cout << BLUE;
	// 	vector<int> v1;
	// 	v1.push_back(0);
	// 	v1.push_back(1);
	// 	v1.push_back(2);
	// 	v1.push_back(3);
	// 	v1.push_back(4);
	// 	v1.push_back(5);
	// 	vector<int>::reverse_iterator it2 = v1.rbegin();
	// 	std::cout << &it2 << std::endl;
	// 	it2++;
	// 	std::cout << *it2 << std::endl;
	// 	std::cout << it2[0] << std::endl;
	// 	std::cout << it2[1] << std::endl;
	// 	it2[1] = 42;
	// 	std::cout << it2[1] << std::endl;
	
	// 	print_vector(v1);
	// 	std::cout << RESET;
	// }
}
