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
	for ( typename V::iterator it = bail.begin(); it != bail.end(); it++)
		std::cout << "it_elem = " << *it << std::endl;
}

int main(void)
{
	// t_struct	elem = {4, "Hello world"};
	// typedef ft::vector<int>::iterator iterator;
	{
		using namespace ft;
		ft::vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		vector<int>::const_iterator it2 = v1.begin();
		std::cout << &it2 << std::endl;
		it2 += 6;
		it2 += -2;
		std::cout << &it2 << std::endl;
		std::cout << it2[0] << std::endl;
		std::cout << it2[1] << std::endl;
		//it2[1] = 42;
		std::cout << it2[1] << std::endl;
	
		print_vector(v1);

		// iterator it = v1.begin();
		// for (; it != v1.end(); it++)
		// {
		// 	std::cout << it->i << std::endl;
		// 	std::cout << it->str << std::endl;
		// }
	}
	{
		using namespace std;
		vector<int> v1;
		v1.push_back(0);
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		vector<int>::const_iterator it2 = v1.begin();
		std::cout << &it2 << std::endl;
		it2 += 6;
		it2 += -2;
		std::cout << BLUE;
		std::cout << &it2 << std::endl;
		std::cout << it2[0] << std::endl;
		std::cout << it2[1] << std::endl;
		//it2[1] = 42;
		std::cout << it2[1] << std::endl;
		std::cout << RESET;
		print_vector(v1);

		// iterator it = v1.begin();
		// for (; it != v1.end(); it++)
		// {
		// 	std::cout << it->i << std::endl;
		// 	std::cout << it->str << std::endl;
		// }
	}
}