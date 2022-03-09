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
    ft::vector<int> v1(5, 42);
    ft::vector<int> v3;
	
	std::cout << BLUE;
	std::cout << "v1.size = " << v1.size() << std::endl;
	std::cout << "v1.capacity = " << v1.capacity() << std::endl;	
	std::cout << "v1.empty() = " << v1.empty() << std::endl;
	std::cout << RESET;
	v1.resize(7, 42);
	std::cout << "v1.size = " << v1.size() << std::endl;
	std::cout << "v1.capacity = " << v1.capacity() << std::endl;
	std::cout << "v1.empty() = " << v1.empty() << std::endl;
	std::cout << RED;
	std::cout << "v1.size = " << v1.size() << std::endl;
	std::cout << "v1.capacity = " << v1.capacity() << std::endl;
	std::cout << "v1.empty() = " << v1.empty() << std::endl;
    std::cout << RESET;
	std::cout << "v3.size = " << v3.size() << std::endl;
	std::cout << "v3.capacity = " << v3.capacity() << std::endl;
	std::cout << "v3.empty() = " << v3.empty() << std::endl;

	std::vector<int> v2(5, 42);
	std::vector<int> v4;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "\033[33m";
	
	std::cout << "v2.size = " << v2.size() << std::endl;
	std::cout << "v2.capacity = " << v2.capacity() << std::endl;	
	std::cout << "v2.empty() = " << v2.empty() << std::endl;
	std::cout << RESET;
	v2.resize(7, 42);
	std::cout << "v2.size = " << v2.size() << std::endl;
	std::cout << "v2.capacity = " << v2.capacity() << std::endl;
	std::cout << "v2.empty() = " << v2.empty() << std::endl;
	std::cout << FIRE;
	std::cout << "v2.size = " << v2.size() << std::endl;
	std::cout << "v2.capacity = " << v2.capacity() << std::endl;
	std::cout << "v2.empty() = " << v2.empty() << std::endl;
    std::cout << std::endl;
	std::cout << RESET;
	print_vector(v1);
	std::cout << "\033[33m";
	print_vector(v2);	
	std::cout << "\033[0m";
	return (0);
}