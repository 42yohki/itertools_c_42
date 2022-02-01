#ifndef REDUCE_H
# define REDUCE_H

typedef void*	(*t_reduce)(void *, void *);

void	*reduce_iter(void *iter, t_reduce reduce, void *init);

#endif
