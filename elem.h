#ifndef ELEM_H
# define ELEM_H

# include "iter.h"

typedef void	(*t_del_elem)(void *);

typedef enum e_it_stat
{
	it_ok,
	it_err,
	it_end
}	t_it_stat;

typedef struct s_elem
{
	t_del_elem	del_elem;
	void		*data;
	t_it_stat	it_stat;
}	t_elem;

void	del_elem(t_elem elem);

#endif
