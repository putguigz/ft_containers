#ifndef __MAP_HPP__
# define __MAP_HPP__

# include "containers.hpp"
# include "utils.hpp"
# include "bst.hpp"

namespace ft{

template < class Key,
			class T,
			class Compare = ft::less< Key >,
			class Alloc = std::allocator< ft::pair<const Key,T> >
			>
class map
{
	public:
		typedef Key                                             key_type;
		typedef T                                               mapped_type;
		typedef ft::pair< const Key, T >                        value_type;
		typedef Compare                                         key_compare;
		typedef Alloc                                           allocator_type;
		typedef typename Alloc::size_type						size_type;
		typedef typename allocator_type::reference              reference;
		typedef typename allocator_type::const_reference        const_reference;
		typedef typename allocator_type::pointer                pointer;
		typedef typename allocator_type::const_pointer          const_pointer;
	
		// typedef ft::MapIterator<ft::map<T, A>, false >          iterator;
		// typedef ft::MapIterator<ft::map<T, A>, true >           const_iterator;
		// typedef ft::reverse_iterator<iterator>                  reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
		// typedef ft::iterator_traits<iterator>::difference_type  difference_type;

		typedef typename std::allocator< BST< value_type, key_compare > >	BST_allocator_type;
		typedef typename BST_allocator_type::pointer						BST_pointer;
		typedef BST_pointer													iterator;
	
	private:
		key_compare							_compare;
		allocator_type						_allocker;
		size_type							_size;
		BST_pointer							_bst;
		BST_allocator_type					_bst_allocker;

	//DELETE ME
	public:
		BST_pointer getBST( void ) const {return _bst;};

	public:
		explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _compare(comp), _allocker(alloc), _size(0), _bst(NULL) { }
		
		map (const map& x) : _compare(x._compare), _allocker(x._allocker), _size(x._size), _bst(NULL) {
			if (x._bst)
				_bst = x._bst->copy_this(_bst);
		 }

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) :  _compare(comp), _allocker(alloc), _bst(NULL) { 
			insert(first, last);
		}

		~map( void ) { destroy_bst(); }

		map&	operator=(const map& x) {
			if (this != &x)
			{
				_compare = x._compare;
				_size = x._size;
				destroy_bst();
				if (x._bst)
					_bst = x._bst->copy_this(x._bst);
				_bst_allocker = x._bst_allocker;
			}
			return (*this);
		}

	private:
		void destroy_bst( void ) {
			if (_bst)
			{
				_bst_allocker.destroy(_bst);
				_bst_allocker.deallocate(_bst, 1);
				_bst = NULL;
			}
		};

	public:
		ft::pair<iterator,bool> insert (const value_type& val){
			ft::pair<BST_pointer, bool> ret;
			if (!_bst)
			{
				_bst = _bst_allocker.allocate(1);
				_bst_allocker.construct(_bst, val);
				ret.first = _bst;
				ret.second = true;
			}
			else
			{
				ret = _bst->insert(val);
				_bst = _bst->rotate(_bst);
				_bst->parent = NULL;
			}
			if (ret.second)
				_size++;
			return (ret);
		}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last){
			for (; first != last; first++)
				insert(*first);
		}

	public:
		size_type size( void ) const { return _size; }
		size_type max_size() const { return _allocker.max_size(); }
		bool empty( void ) const { return (_size == 0 ? true : false); }
		allocator_type get_allocator( void ) const { return _allocker; }
		key_compare key_comp() const { return _compare; }
		void swap (map& x) { map<key_type, mapped_type> tmp(this); this = x; x = tmp; };
};


}

#endif