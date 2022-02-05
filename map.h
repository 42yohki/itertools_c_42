#ifndef MAP_H
# define MAP_H

# include "iter.h"
# include "elem.h"

typedef void	*(*t_map)(void *);

typedef struct s_map_iter
{
	t_base_iter	base_iter;
	void		*in_iter;
	t_map		map;
	t_del_elem	del_elem;
}	t_map_iter;

t_map_iter	*map(void *iter, t_map map, t_del_elem del_elem);

#endif
