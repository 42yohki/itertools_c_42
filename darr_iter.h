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

t_darr_iter	*get_darr_iter(t_darr *darr);
void		*collect_darr(void *prev, void *curr);

#endif
