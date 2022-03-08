#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include "containers.hpp"

namespace ft{

template < typename T, typename A = std::allocator<T> >
class vector{
    
    public:
     
        typedef T value_type;
        typedef A allocator_type;

        //DIG THOSE
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        /* THERE IS MORE TO ADD HERE
        ...
        */

        //CONSTRUCTOR
        vector( void );
        ~vector( void );

        //PUBLIC FCT
        allocator_type get_allocator( void ) const;

    private:
        allocator_type _allocker;


};

//CONSTRUCTOR................................................................//
template < typename T, typename A >
vector<T, A>::vector( void )
{
    std::cout << "Hello World" << std::endl;
    return ;
}

//DESTRUCTOR................................................................//
template < typename T, typename A >
vector<T, A>::~vector( void )
{
    std::cout << "BYE WORLD" << std::endl;
    return ;
}

//PUBLIC FUNCTIONS..........................................................//
template < typename T, typename A >
typename vector<T, A>::allocator_type vector<T, A>::get_allocator( void ) const { return _allocker;}





}

#endif