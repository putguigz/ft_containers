#ifndef __MAP_HPP__
# define __MAP_HPP__

# include "containers.hpp"
# include "utils.hpp"
# include "bst.hpp"
# include "map_iterator.hpp"

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
		typedef typename allocator_type::difference_type		difference_type;

		typedef typename std::allocator< BST< value_type, key_compare > >	BST_allocator_type;
		typedef typename BST_allocator_type::pointer						BST_pointer;
		typedef typename ft::MapIterator< map<Key, T>, false  >				iterator;
		typedef typename ft::MapIterator< const map<Key, T>, true >			const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	
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
				_bst = x._bst->copy_this();
		 }

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) :  _compare(comp), _allocker(alloc), _size(0), _bst(NULL) { 
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
					_bst = x._bst->copy_this();
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
				_size = 0;
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
				balance(_bst);
				_bst = rotate(_bst);
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

		iterator insert (iterator position, const value_type& val)
		{
			static_cast<void>(position);
			ft::pair<iterator, bool> ret = insert(val);
			return (ret.first);
		}

		void		erase( iterator position )
		{	
			if (!_bst)
				return ;
			else
			{
				if (position == _bst)
				{
					_bst = destroy(_bst);
					if (_bst)
					{
						balance(_bst);
						_bst = rotate(_bst);
						_bst->parent = NULL;
					}
					_size--;
					return ;
				}
				else
				{
					BST_pointer d_stroy = position.base();
					BST_pointer parent = d_stroy->parent;
					BST_pointer parent2 = parent->parent;
					if (parent->left == d_stroy)
						parent->left = destroy(d_stroy);
					else
						parent->right = destroy(d_stroy);
					balance(parent);
					if (parent2)
					{
						if (parent2->left == parent)
							parent2->left = rotate(parent);
						else
							parent2->right = rotate(parent);
					}
					_bst->recursive_balancing();
					_size--;
					return ;
				}
			}
		}

		void		erase(iterator first, iterator last)
		{
			while (first != last)
			{
				print2D(_bst);
				erase(first++);
			}
		}

		size_type	erase(const key_type & k)
		{
			if (!_bst)
				return 0;
			if (_bst->elem.first == k)
			{
				_bst = destroy(_bst);
				if (_bst)
				{
					balance(_bst);
					_bst = rotate(_bst);
					_bst->parent = NULL;
				}
				_size--;
				return 1;
			}
			if (_bst->erase_elem(k))
			{
				balance(_bst);
				_bst = rotate(_bst);
				_bst->parent = NULL;
				_size--;
				return 1;
			}
			else
				return 0;
		}

	//ITERATORS//
	public:
		iterator begin( void ) {
			if (_bst)
				return (iterator(_bst->find_start()));
			else
				return (iterator());
		}

		const_iterator begin() const {
			if (_bst)
				return (const_iterator(_bst->find_start()));
			else
				return (const_iterator());
		};


		iterator end( void ){
			if (_bst)
			{
				iterator past_end = iterator(_bst->find_end());
				past_end.setOut(true);
				past_end.setOffset(1);
				return (past_end);
			}
			else
				return (iterator());
		}

		const_iterator end( void ) const {
			if (_bst)
			{
				const_iterator past_end = const_iterator(_bst->find_end());
				past_end.setOut(true);
				past_end.setOffset(1);
				return (past_end);
			}
			else
				return (const_iterator());
		}

		iterator find (const key_type& k){
			if (_bst)
			{
				BST_pointer tmp = _bst->find_by_key(k);
				if (tmp)
					return (iterator(tmp));
				else
					return (end());
			}
			else
				return (iterator());	
		}

		const_iterator find (const key_type& k) const{
			if (_bst)
			{
				BST_pointer tmp = _bst->find_by_key(k);
				if (tmp)
					return (const_iterator(tmp));
				else
					return (end());
			}
			else
				return (const_iterator());
		}

		size_type	count( const key_type& k) const{
			if (_bst)
			{
				BST_pointer tmp = _bst->find_by_key(k);
				if (tmp)
					return 1;
				else
					return 0;
			}
			else
				return 0;
		}

		iterator lower_bound (const key_type& k)
		{
			if (_bst)
			{
				iterator it = begin();
				iterator it_end = end();
				for (; it != it_end; it++)
				{
					if (!_compare(it->first, k))
						break;
				}
				return (it);
			}
			else
				return (iterator());
		}

		const_iterator lower_bound (const key_type& k) const
		{
			if (_bst)
			{
				const_iterator it = begin();
				const_iterator it_end = end();
				for (; it != it_end; it++)
				{
					if (!_compare(it->first, k))
						break;
				}
				return (it);
			}
			else
				return (const_iterator());
		}
	
		iterator upper_bound (const key_type& k){
			if (_bst)
			{
				iterator it = begin();
				iterator it_end = end();
				for (; it != it_end; it++)
				{
					if (!_compare(it->first, k))
					{
						if (it->first == k)
							it++; 
						break;
					}
				}
				return (it);
			}
			else
				return (iterator());
		}

		const_iterator upper_bound (const key_type& k) const{
			if (_bst)
			{
				const_iterator it = begin();
				const_iterator it_end = end();
				for (; it != it_end; it++)
				{
					if (!_compare(it->first, k))
						break;
				}
				return (it);
			}
			else
				return (const_iterator());
		}

	public:
		void clear() { destroy_bst(); };
		size_type size( void ) const { return _size; }
		size_type max_size() const { return _allocker.max_size(); }
		bool empty( void ) const { return (_size == 0 ? true : false); }
		allocator_type get_allocator( void ) const { return _allocker; }
		key_compare key_comp() const { return _compare; }
		void swap (map& x) { map<key_type, mapped_type> tmp(this); this = x; x = tmp; };
};


}

#endif