#include <stdlib.h>
#include "map.h"
#include "iter.h"
#include "elem.h"

// mutable

t_elem	map_next(t_map_iter *iter)
{
	t_elem	elem;

	elem = next(iter->in_iter);
	if (elem.it_stat == it_ok)
		iter->map(elem.data);
	return (elem);
}

void	map_del(void *iter)
{
	del_iter(((t_map_iter *)iter)->in_iter);
	free(iter);
}

t_map_iter	*map(void *iter, t_map map)
{
	t_map_iter	*map_iter;

	if (!iter)
		return (NULL);
	map_iter = malloc(sizeof(t_map_iter));
	if (!map_iter)
	{
		((t_base_iter *)iter)->del_iter(iter);
		return (NULL);
	}
	map_iter->base_iter.next = map_next;
	map_iter->base_iter.del_iter = map_del;
	map_iter->in_iter = iter;
	map_iter->map = map;
	return (map_iter);
}

// immutable

t_elem	new_map_next(t_new_map_iter *iter)
{
	t_elem	elem;
	t_elem	new_elem;

	elem = next(iter->in_iter);
	if (elem.it_stat == it_ok)
	{
		new_elem.data = iter->new_map(elem.data);
		if (new_elem.data)
			new_elem.it_stat = it_ok;
		else
			new_elem.it_stat = it_err;
		del_elem(elem);
		new_elem.del_elem = iter->del_elem;
		return (new_elem);
	}
	return (elem);
}

void	new_map_del(void *iter)
{
	del_iter(((t_new_map_iter *)iter)->in_iter);
	free(iter);
}

t_new_map_iter	*new_map(void *iter, t_new_map new_map, t_del_elem del_elem)
{
	t_new_map_iter	*new_map_iter;

	if (!iter)
		return (NULL);
	new_map_iter = malloc(sizeof(t_new_map_iter));
	if (!new_map_iter)
	{
		((t_base_iter *)iter)->del_iter(iter);
		return (NULL);
	}
	new_map_iter->base_iter.next = new_map_next;
	new_map_iter->base_iter.del_iter = new_map_del;
	new_map_iter->in_iter = iter;
	new_map_iter->new_map = new_map;
	new_map_iter->del_elem = del_elem;
	return (new_map_iter);
}
