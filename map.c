#include <stdlib.h>
#include "map.h"
#include "iter.h"
#include "elem.h"

t_elem	map_next(t_map_iter *iter)
{
	t_elem	elem;
	t_elem	new_elem;

	elem = next(iter->in_iter);
	if (elem.it_stat == it_ok)
	{
		new_elem.data = iter->map(elem.data);
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

void	map_del(void *iter)
{
	del_iter(((t_map_iter *)iter)->in_iter);
	free(iter);
}

t_map_iter	*map(void *iter, t_map map, t_del_elem del_elem)
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
	map_iter->del_elem = del_elem;
	return (map_iter);
}
