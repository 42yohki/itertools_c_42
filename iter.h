#ifndef ITER_H
# define ITER_H

# include "elem.h"

struct					s_elem;
typedef void			(*t_del_iter) (void *);
typedef struct s_elem	(*t_next) ();

typedef struct s_base_iter
{
	t_next		next;
	t_del_iter	del_iter;
}	t_base_iter;

struct s_elem	next(void *iter);
void			del_iter(void *iter);

#endif
