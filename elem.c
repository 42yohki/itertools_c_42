#include "elem.h"

void	del_elem(t_elem elem)
{
	if (elem.del_elem)
		elem.del_elem(elem.data);
}
