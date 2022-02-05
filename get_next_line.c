#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"
#include "elem.h"
#include "iter.h"
#include "str.h"

// getc_iter
t_elem	getc_iter_next(t_getc_iter *iter)
{
	if (iter->pos >= iter->ret)
	{
		iter->ret = read(iter->fd, iter->buf, BUFFER_SIZE);
		if (iter->ret == -1)
			return (err_elem());
		else if (iter->ret == 0)
			return (end_elem());
		iter->pos = 0;
	}
	return (ok_elem(&iter->buf[iter->pos++], NULL));
}

void	getc_iter_del(void *iter)
{
	free(iter);
}

t_getc_iter	*getc_iter(int fd)
{
	t_getc_iter	*iter;

	iter = malloc(sizeof(t_getc_iter));
	if (!iter)
		return (NULL);
	iter->base_iter.next = getc_iter_next;
	iter->base_iter.del_iter = getc_iter_del;
	iter->fd = fd;
	iter->pos = 0;
	iter->ret = 0;
	return (iter);
}

// gnl_iter
t_elem	gnl_iter_next(t_gnl_iter *iter)
{
	t_elem	getc_elem;
	t_str	*line;

	line = str_new();
	if (!line)
		return (err_elem());
	while (next_elem(&getc_elem, iter->getc_iter) == it_ok)
	{
		if (!str_add(line, *(char *)getc_elem.data))
		{
			str_del(line);
			return (err_elem());
		}
		if (str_get(line, str_len(line) - 1) == '\n')
			return (ok_elem(line, (t_del_elem)str_del));
	}
	if (getc_elem.it_stat == it_end)
	{
		if (str_len(line) == 0)
		{
			str_del(line);
			return (end_elem());
		}
		return (ok_elem(line, (t_del_elem)str_del));
	}
	str_del(line);
	return (err_elem());
}

void	gnl_iter_del(void *iter)
{
	del_iter(((t_gnl_iter *)iter)->getc_iter);
	free(iter);
}

t_gnl_iter	*gnl_iter(int fd)
{
	t_gnl_iter	*iter;

	iter = malloc(sizeof(t_gnl_iter));
	if (!iter)
		return (NULL);
	iter->base_iter.next = gnl_iter_next;
	iter->base_iter.del_iter = gnl_iter_del;
	iter->getc_iter = getc_iter(fd);
	if (!iter->getc_iter)
	{
		gnl_iter_del(iter);
		return (NULL);
	}
	return (iter);
}

// get_next_line
char	*get_next_line(int fd)
{
	static t_gnl_iter	*iter = NULL;
	t_elem				elem;
	t_str				*line;
	char				*c_str;

	if (!iter)
	{
		iter = gnl_iter(fd);
		if (!iter)
			return (NULL);
	}
	if (next_elem(&elem, iter) == it_ok)
	{
		line = (t_str *)elem.data;
		c_str = str_c_str(line);
		str_del(line);
		if (!c_str)
			return (NULL);
		return (c_str);
	}
	else
	{
		del_iter(iter);
		iter = NULL;
		return (NULL);
	}
}
