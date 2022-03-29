	pointer find_by_key( key_type key )
	{
		if (cmp(key, this->elem.first))
		{
			if (left)
				return (left->find_by_key(key));
			else
				return NULL;
		}
		else
		{
			if (key == this->elem.first)
				return this;
			else if (right)
				return (right->find_by_key(key));
			else
				return NULL;
		}
	}

	int	destroy_no_child(pointer d_ptr)
	{
		pointer parent = d_ptr->parent;
		if (!parent)
			return 0;
		else
		{
			if (d_ptr == parent->left)
			{
				destroy_pointer(parent->left);
				return 1;
			}
			else
			{
				destroy_pointer(parent->right);
				return -1;
			}
		}
	}

	void	destroy_mono_child( pointer d_ptr )
	{
		pointer parent = d_ptr->parent;
		pointer save_me;
		if (d_ptr->left)
			save_me = d_ptr->left;
		else
			save_me = d_ptr->right;
		d_ptr->left = NULL;
		d_ptr->right = NULL;
		int ret = destroy_no_child(d_ptr);
		if (ret > 0)
			parent->left = save_me;
		else if (ret < 0)
			parent->right = save_me;
		save_me->parent = parent;
	}

	void	destroy_two_child( pointer d_ptr )
	{
		static bool flag = true;

		pointer closest_node;
		if (flag)
		{
			flag = false;
			closest_node = d_ptr->right;
			while (closest_node->left)
				closest_node = closest_node->left;
			std::cout << "closest_node->elem.first1 = " << closest_node->elem.first << std::endl;
		}
		else
		{
			std::cout << "d_ptr->elem.first2 = " << d_ptr->elem.first << std::endl;
			flag = true;
			closest_node = d_ptr->left;
			while (closest_node->right)
				closest_node = closest_node->right;
		}
		d_ptr->elem = closest_node->elem;
		if (!closest_node->left && !closest_node->right)
			destroy_no_child(closest_node);
		if ((!closest_node->left && closest_node->right) || (closest_node->left && !closest_node->right))
			destroy_mono_child(closest_node);
	}

	void	erase_elem( key_type key )
	{
		pointer d_stroy = find_by_key(key);
		if (!d_stroy)
			return ;
		if (!d_stroy->left && !d_stroy->right)
			destroy_no_child(d_stroy);
		if ((!d_stroy->left && d_stroy->right) || (d_stroy->left && !d_stroy->right))
			destroy_mono_child(d_stroy);
		if (d_stroy->left && d_stroy->right)
			destroy_two_child(d_stroy);
		recursive_balancing();
	}