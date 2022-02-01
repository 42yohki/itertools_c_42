#include <stdlib.h>
#include <stdbool.h>
#include "range.h"
#include "iter.h"
#include "elem.h"

t_elem	range_next(t_range_iter *iter)
{
	t_elem	elem;

	elem.del_elem = NULL;
	if (iter->i < iter->end)
	{
		elem.data = &iter->i;
		elem.it_stat = it_ok;
		iter->i++;
	}
	else
	{
		elem.data = NULL;
		elem.it_stat = it_end;
	}
	return (elem);
}

void	range_del(void *iter)
{
	free(iter);
}

t_range_iter	*range_iter(int start, int end)
{
	t_range_iter	*range_iter;

	range_iter = malloc(sizeof(t_range_iter));
	if (!range_iter)
		return (NULL);
	range_iter->base_iter.next = range_next;
	range_iter->base_iter.del_iter = range_del;
	range_iter->start = start;
	range_iter->end = end - 1;
	range_iter->i = start - 1;
	return (range_iter);
}
