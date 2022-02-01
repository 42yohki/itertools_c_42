#ifndef FOREACH_H
# define FOREACH_H

typedef void	(*t_callback)(void *);

void	foreach(void *iter, t_callback callback);

#endif
