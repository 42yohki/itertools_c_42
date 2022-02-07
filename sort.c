#include <stdlib.h>
#include "sort.h"
#include "iter.h"
#include "elem.h"
#include "darr.h"
#include "darr_iter.h"

t_elem	sort_next(t_sort_iter *iter)
{
	return (next(iter->darr_iter));
}

void	sort_del(void *iter)
{
	darr_del(((t_sort_iter *)iter)->darr);
	del_iter(((t_sort_iter *)iter)->darr_iter);
	free(iter);
}

t_sort_iter	*sort(void *iter, t_compare compare)
{
	t_sort_iter	*sort_iter;

	if (!iter)
		return (NULL);
	sort_iter = calloc(1, sizeof(t_sort_iter));
	if (!sort_iter)
	{
		((t_base_iter *)iter)->del_iter(iter);
		return (NULL);
	}
	sort_iter->base_iter.next = sort_next;
	sort_iter->base_iter.del_iter = sort_del;
	sort_iter->darr = darr_collect(iter);
	if (!sort_iter->darr)
	{
		sort_del(sort_iter);
		return (NULL);
	}
	qsort(sort_iter->darr->_arr, sort_iter->darr->_len, sizeof(void *), compare);
	sort_iter->darr_iter = darr_iter(sort_iter->darr);
	if (!sort_iter->darr_iter)
	{
		sort_del(sort_iter);
		return (NULL);
	}
	return (sort_iter);
}
