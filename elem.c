#include <stddef.h>
#include "elem.h"

void	del_elem(t_elem elem)
{
	if (elem.del_elem)
		elem.del_elem(elem.data);
}

t_elem	create_elem(void *data, t_it_stat stat, t_del_elem del)
{
	t_elem	elem;

	elem.data = data;
	elem.it_stat = stat;
	elem.del_elem = del;
	return (elem);
}

t_elem	err_elem(void)
{
	return (create_elem(NULL, it_err, NULL));
}

t_elem	end_elem(void)
{
	return (create_elem(NULL, it_end, NULL));
}

t_elem	ok_elem(void *data, t_del_elem del)
{
	return (create_elem(data, it_ok, del));
}

t_it_stat	next_elem(t_elem *elem, void *iter)
{
	*elem = next(iter);
	return (elem->it_stat);
}
