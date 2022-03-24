#ifndef __MAP_HPP__
# define __MAP_HPP__

# include "utils.hpp"
# include "bst.hpp"

namespace ft{

template < class Key,
            class T,
            class Compare = ft::less< Key >,
            class Alloc = allocator< ft::pair<const Key,T> >
            >
class map
{
    public:
        typedef Key                                             key_type;
        typedef T                                               mapped_type;
        typedef ft::pair< const Key, T >                        value_type;
        typedef Compare                                         key_compare;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        // typedef ft::MapIterator<ft::map<T, A>, false >          iterator;
        // typedef ft::MapIterator<ft::map<T, A>, true >           const_iterator;
        // typedef ft::reverse_iterator<iterator>                  reverse_iterator;
        // typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
        // typedef ft::iterator_traits<iterator>::difference_type  difference_type;
        typedef A::size_type                                    size_type;
    
    private:
        value_compare                       _compare;
        allocator_type                      _allocker;
        size_type                           _size;
        BST<value_type, key_compare>**    _bst;

    public:
        explicit map (const key_compare& comp = key_compare(), 
                const allocator_type& alloc = allocator_type()) : _compare(comp), _allocker(alloc), _bst(NULL) { }
        
        map (const map& x) : _compare(x._compare), _allocker(x._allocker), _bst(NULL) { /*ADD COPY*/ }

        template <class InputIterator>
        map (InputIterator first, InputIterator last,
        const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type()) :  _compare(comp), _allocker(alloc), _bst(NULL) { /*DO THINGS*/ }

        ~map( void ) { /* DESTROY AND DEALLOCATE ELEMS */ }

        map&    operator=(const map& x) { /*Depends ON IMPLEMENTATION + SIZE etc...*/ }
        allocator_type get_allocator( void ) const { return _allocker; }
};


}

#endif