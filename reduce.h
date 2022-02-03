#ifndef REDUCE_H
# define REDUCE_H

typedef void*	(*t_reduce)(void *, void *);
typedef void	(*t_del_sum)(void *);

void	*reduce(void *iter, t_reduce reduce, void *init, t_del_sum del_sum);

#endif
