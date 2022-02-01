#include "foreach.h"
#include "elem.h"
#include "iter.h"

void	foreach(void *iter, t_callback callback)
{
	t_elem	elem;

	if (!iter)
		return ;
	elem = next(iter);
	while (elem.it_stat == it_ok)
	{
		callback(elem.data);
		del_elem(elem);
		elem = next(iter);
	}
	del_iter(iter);
}
