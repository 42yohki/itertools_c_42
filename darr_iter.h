#ifndef DARR_ITER_H
# define DARR_ITER_H

# include "iter.h"
# include "darr.h"

typedef struct s_darr_iter
{
	t_base_iter	base_iter;
	t_darr		*darr;
	size_t		index;
}	t_darr_iter;

t_darr_iter	*darr_iter(t_darr *darr);
t_darr		*darr_collect(void *iter);

#endif
