#ifndef FILTER_H
# define FILTER_H

# include <stdbool.h>
# include "iter.h"

typedef bool	(*t_filter)(void *);

typedef struct s_filter_iter
{
	t_base_iter	base_iter;
	void		*in_iter;
	t_filter	filter;
}	t_filter_iter;

t_filter_iter	*filter(void *iter, t_filter filter);

#endif
