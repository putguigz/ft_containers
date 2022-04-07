#include <utility>
#include <functional>
#include <iostream>
#include <string>
#include <iomanip>

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

# define ERR_NO_NUM -1
# define ERR_NO_MEM -2


int myRandom (int size) {
    int i, n;
    static int numNums = 0;
    static int *numArr = NULL;

    if (size >= 0) {
        if (numArr != NULL)
            free (numArr);
        if ((numArr = (int *)malloc (sizeof(int) * size)) == NULL)
            return ERR_NO_MEM;
        for (i = 0; i  < size; i++)
            numArr[i] = i;
        numNums = size;
    }
    if (numNums == 0)
       return ERR_NO_NUM;
    n = rand() % numNums;
    i = numArr[n];
    numArr[n] = numArr[numNums-1];
    numNums--;
    if (numNums == 0) {
        free (numArr);
        numArr = 0;
    }

    return i;
}

template <typename T>
int printVector( vector<T> const & vec)
{
	std::cout << "<--------  VECTOR PRINT   ---------->"
	std::cout << "SIZE : [" << vec.size() << "]" << std::endl;
	
	if (vec.size() > 0)
	{
		std::cout << setw(10) << "CONTENT : ["
		vector<T>::iterator it = vector.begin();
		for (; it != vector.end(); it++)
			std::cout << 
	}
	std::cout << "<--------  END OF PRINT   ---------->"
}

int main(void)
{
	{
		std::cout << "%*************************************************************%" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "*                      VECTOR_CONSTRUCTORS                    *" << std::endl;
		std::cout << "*                                                             *" << std::endl;
		std::cout << "%*************************************************************%" << std::endl;

		vector<int> vi;
		vector<int> second(4, 100);
	}	
}
