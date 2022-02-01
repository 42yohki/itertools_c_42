#ifndef RANGE_H
# define RANGE_H

# include "iter.h"

typedef struct s_range_iter
{
	t_base_iter	base_iter;
	int			start;
	int			end;
	int			i;
}	t_range_iter;

t_range_iter	*range_iter(int start, int end);

#endif
