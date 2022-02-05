#ifndef DARR_H
# define DARR_H
# include <stddef.h>
# include <stdbool.h>

typedef struct s_darr
{
	void		**_arr;
	size_t		_cap;
	size_t		_len;
	void		(*_del)(void *);
}	t_darr;

t_darr	*darr_new(size_t nmemb, void (*del)(void *));
void	darr_del(t_darr *darr);
size_t	darr_len(t_darr *darr);
void	darr_set(t_darr *darr, size_t index, void *data);
void	*darr_get(t_darr *darr, size_t index);
bool	darr_add(t_darr *darr, void *data);
void	darr_set_del(t_darr *darr, void (*del)(void *));

#endif
