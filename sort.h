#ifndef SORT_H
# define SORT_H

# include <stdbool.h>
# include "iter.h"
# include "darr.h"
# include "darr_iter.h"

typedef int	(*t_compare)(const void *, const void *);

typedef struct s_sort_iter
{
	t_base_iter	base_iter;
	t_darr		*darr;
	t_darr_iter	*darr_iter;
}	t_sort_iter;

t_sort_iter	*sort(void *iter, t_compare compare);

#endif
