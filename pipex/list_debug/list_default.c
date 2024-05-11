int	lst_node_get_absolute_position(list *node, enum_memb orientation, int offset_value, int offset_direction, int value)
{
	int i;

	i = 0;
	if (!node)
		return (-1);
	if (orientation == FRONT)
		while (node->prev)
			node = node->prev;
	else
		node = lst_node_last(node);
	while (node)
	{
		if (*(int *)((char *)node + offset_value) == value)
			return (i);
		 node = *(list **)((char *)node + offset_direction);
		i++;
	}
	return (-1);
}


int	lst_get_extreme_information(list *node, enum_memb extreme, unsigned int offset)
{
	int i;
	if (!node)
		return (-1);
	if (node->size == 0)
		return (node->value);
	if (extreme == MAXIMUM)
		i = 0;
	else
		i = 2147483647;
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (extreme == MAXIMUM)
		{
			if (i < *(int *)((char *)node + offset))
				i = *(int *)((char *)node + offset);
		}
		else if (extreme == MINIMUM)
		{
			if (i > *(int *)((char *)node + offset))
				i = *(int *)((char *)node + offset);
		}
		node = node->next;
	}
	return (i);
}
