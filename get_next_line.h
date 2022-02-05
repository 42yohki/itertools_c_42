#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include "iter.h"
# include "str.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_getc_iter
{
	t_base_iter	base_iter;
	int			fd;
	char		buf[BUFFER_SIZE];
	ssize_t		pos;
	ssize_t		ret;
}	t_getc_iter;

typedef struct s_gnl_iter
{
	t_base_iter	base_iter;
	t_getc_iter	*getc_iter;
}	t_gnl_iter;

char	*get_next_line(int fd);

#endif
