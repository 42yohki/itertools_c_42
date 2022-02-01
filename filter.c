#include <stdlib.h>
#include "filter.h"
#include "iter.h"
#include "elem.h"

t_elem	filter_next(t_filter_iter *iter)
{
	t_elem	elem;

	elem = next(iter->in_iter);
	while (elem.it_stat == it_ok)
	{
		if (iter->filter(elem.data))
			break ;
		else
			del_elem(elem);
		elem = next(iter->in_iter);
	}
	return (elem);
}

void	filter_del(void *iter)
{
	del_iter(((t_filter_iter *)iter)->in_iter);
	free(iter);
}

t_filter_iter	*filter_iter(void *iter, t_filter filter)
{
	t_filter_iter	*filter_iter;

	if (!iter)
		return (NULL);
	filter_iter = malloc(sizeof(t_filter_iter));
	if (!filter_iter)
	{
		((t_base_iter *)iter)->del_iter(iter);
		return (NULL);
	}
	filter_iter->base_iter.next = filter_next;
	filter_iter->base_iter.del_iter = filter_del;
	filter_iter->in_iter = iter;
	filter_iter->filter = filter;
	return (filter_iter);
}
