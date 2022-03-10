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
	for (unsigned long i = 0; i != bail.size(); i++)
		std::cout << "bail[i] = " << bail[i] << std::endl;
}

int main(void)
{
	//t_struct	elem = {4, "Hello world"};
	typedef ft::vector<int>::iterator iterator;

    ft::vector<int> v1;
	//v1.push_back(elem);
	v1.push_back(18);
	v1.push_back(19);
	v1.push_back(20);
	v1.push_back(21);
	v1.push_back(22);
	print_vector(v1);

	iterator it = v1.begin();
	for (; it != v1.end(); it++)
	{
		std::cout << it->i << std::endl;
		std::cout << it->str << std::endl;
	}
}