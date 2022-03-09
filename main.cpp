#include "containers.hpp"
#include "vector.hpp"
#include <vector>

# define RED "\033[38;5;124m"
# define RESET "\033[0m"
# define BLUE "\033[38;5;63m"
# define GREEN "\033[38;5;42m"
# define FIRE "\033[38;5;166m"
# define PURPLE "\033[38;5;105m"
# define LIGHTBLUE "\033[38;5;87m"
# define YELLOW "\033[38;5;220m"
# define DEV "\033[38;5;200m"

template < typename V >
void	print_vector(V & bail)
{
	for (unsigned long i = 0; i != bail.size(); i++)
		std::cout << "bail[i] = " << bail[i] << std::endl;
}

int main(void)
{
    using namespace ft;
    
    vector<int> v1(10, 42);
	vector<int> v2(10, 42);
    
	std::cout << BLUE;
	std::cout << "v1.size = " << v1.size() << std::endl;
	std::cout << "v1.capacity = " << v1.capacity() << std::endl;	
	std::cout << "v1.empty() = " << v1.empty() << std::endl;
	std::cout << RESET;
	v1.reserve(100);
	std::cout << "v1.size = " << v1.size() << std::endl;
	std::cout << "v1.capacity = " << v1.capacity() << std::endl;
	std::cout << "v1.empty() = " << v1.empty() << std::endl;
	v1.resize(50);
	std::cout << RED;
	std::cout << "v1.size = " << v1.size() << std::endl;
	std::cout << "v1.capacity = " << v1.capacity() << std::endl;
	std::cout << "v1.empty() = " << v1.empty() << std::endl;
    std::cout << RESET;
	print_vector(v1);
	
	using namespace std;
	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "\033[33m";
	
	std::cout << "v2.size = " << v2.size() << std::endl;
	std::cout << "v2.capacity = " << v2.capacity() << std::endl;	
	std::cout << "v2.empty() = " << v2.empty() << std::endl;
	std::cout << std::endl;
	v2.reserve(100);
	std::cout << "v2.size = " << v2.size() << std::endl;
	std::cout << "v2.capacity = " << v2.capacity() << std::endl;
	std::cout << "v2.empty() = " << v2.empty() << std::endl;
	v2.resize(50);
	std::cout << "v2.size = " << v2.size() << std::endl;
	std::cout << "v2.capacity = " << v2.capacity() << std::endl;
	std::cout << "v2.empty() = " << v2.empty() << std::endl;
    print_vector(v2);
	
	std::cout << "\033[0m";
	return (0);
}