#include <stdlib.h>
#include "darr.h"
#include "darr_iter.h"
#include "elem.h"
#include "iter.h"

t_elem	darr_iter_next(t_darr_iter *iter)
{
	t_elem	elem;

	elem.del_elem = NULL;
	if (iter->index < darr_len(iter->darr))
	{
		elem.data = darr_get(iter->darr, iter->index);
		elem.it_stat = it_ok;
		iter->index++;
	}
	else
	{
		elem.data = NULL;
		elem.it_stat = it_end;
	}
	return (elem);
}

void	darr_iter_del(void *iter)
{
	free(iter);
}

t_darr_iter	*get_darr_iter(t_darr *darr)
{
	t_darr_iter	*iter;

	iter = malloc(sizeof(t_darr_iter));
	if (!iter)
		return (NULL);
	iter->base_iter.next = darr_iter_next;
	iter->base_iter.del_iter = darr_iter_del;
	iter->darr = darr;
	iter->index = 0;
	return (iter);
}

void	*collect_darr(void *prev, void *curr)
{
	t_darr	*darr;

	darr = (t_darr *)prev;
	if (!darr)
		return (NULL);
	if (!darr_add(darr, curr))
	{
		darr_del(darr);
		return (NULL);
	}
	return (darr);
}
