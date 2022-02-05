#include <stdlib.h>
#include "reduce.h"
#include "elem.h"
#include "iter.h"

void	*reduce(void *iter, t_reduce reduce, void *init, t_del_sum del_sum)
{
	t_elem	elem;
	void	*sum;
	void	*new_sum;

	if (!iter)
		return (NULL);
	if (!init)
	{
		del_iter(iter);
		return (NULL);
	}
	sum = init;
	elem = next(iter);
	while (elem.it_stat == it_ok)
	{
		new_sum = reduce(sum, elem.data);
		del_sum(sum);
		del_elem(elem);
		if (!new_sum)
			break;
		sum = new_sum;
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
