#include "iter.h"
#include "elem.h"

void	del_iter(void *iter)
{
	t_base_iter	*base_iter;

	if (!iter)
		return ;
	base_iter = (t_base_iter *)iter;
	if (base_iter->del_iter)
		base_iter->del_iter(iter);
}

t_elem	next(void *iter)
{
	t_base_iter	*base_iter;

	base_iter = (t_base_iter *)iter;
	return (base_iter->next(iter));
}
