#include <stdlib.h>
#include "darr.h"
#include "darr_iter.h"
#include "elem.h"
#include "iter.h"
#include "reduce.h"

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

t_darr_iter	*darr_iter(t_darr *darr)
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

t_darr	*darr_collect(void *iter)
{
	t_darr	*darr;
	t_elem	elem;

	if (!iter)
		return (NULL);
	darr = darr_new(0, NULL);
	if (!darr)
	{
		del_iter(iter);
		return (NULL);
	}
	elem = next(iter);
	if (elem.it_stat == it_ok)
		darr_set_del(darr, elem.del_elem);
	while (elem.it_stat == it_ok)
	{
		if (!darr_add(darr, elem.data))
		{
			del_elem(elem);
			del_iter(iter);
			darr_del(darr);
			return (NULL);
		}
		elem = next(iter);
	}
	del_iter(iter);
	if (elem.it_stat == it_err)
	{
		darr_del(darr);
		return (NULL);
	}
	return (darr);
}
