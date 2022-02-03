#ifndef MAP_H
# define MAP_H

# include "iter.h"
# include "elem.h"

typedef void	(*t_map)(void *);
typedef void	*(*t_new_map)(void *);

typedef struct s_map_iter
{
	t_base_iter	base_iter;
	void		*in_iter;
	t_map		map;
}	t_map_iter;

typedef struct s_new_map_iter
{
	t_base_iter	base_iter;
	void		*in_iter;
	t_new_map	new_map;
	t_del_elem	del_elem;
}	t_new_map_iter;

t_map_iter		*map(void *iter, t_map map);
t_new_map_iter	*new_map(void *iter, t_new_map new_map, t_del_elem del_elem);

#endif
