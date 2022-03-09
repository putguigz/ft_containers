#include "containers.hpp"
#include "vector.hpp"
#include <vector>

template < typename V >
void	print_vector(V & bail)
{
	for (unsigned long i = 0; i != bail.size(); i++)
		std::cout << "bail[i] = " << bail[i] << std::endl;
}

int main(void)
{    
    ft::vector<int> v1(10, 42);
	v1.push_back(18);
	v1.push_back(19);
	v1.push_back(20);
	v1.push_back(21);
	v1.push_back(22);
	print_vector(v1);

	ft::vector<int>::iterator it;
}