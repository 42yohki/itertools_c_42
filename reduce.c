#include <stdlib.h>
#include "reduce.h"
#include "elem.h"
#include "iter.h"

void	*reduce_iter(void *iter, t_reduce reduce, void *init, t_del_sum del_sum)
{
	t_elem	elem;
	void	*sum;

	if (!iter)
		return (NULL);
	sum = init;
	elem = next(iter);
	while (elem.it_stat == it_ok)
	{
		sum = reduce(sum, elem.data);
		del_elem(elem);
		if (!sum)
			break ;
		elem = next(iter);
	}
	del_iter(iter);
	if (elem.it_stat == it_err)
	{
		if (del_sum)
			del_sum(sum);
		return (NULL);
	}
	return (sum);
}
