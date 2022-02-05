#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"
#include "elem.h"
#include "iter.h"
#include "str.h"

t_elem	getc_iter_next(t_getc_iter *iter)
{
	t_elem	elem;

	elem.del_elem = NULL;
	if (iter->pos >= iter->ret)
	{
		iter->ret = read(iter->fd, iter->buf, BUFFER_SIZE);
		if (iter->ret == -1)
		{
			elem.it_stat = it_err;
			return (elem);
		}
		else if (iter->ret == 0)
		{
			elem.it_stat = it_end;
			return (elem);
		}
		iter->pos = 0;
	}
	elem.data = &iter->buf[iter->pos];
	iter->pos++;
	elem.it_stat = it_ok;
	return (elem);
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

t_elem	gnl_iter_next(t_gnl_iter *iter)
{
	t_elem	elem;
	t_elem	getc_elem;
	t_str	*line;

	elem.del_elem = (t_del_elem)str_del;
	line = str_new();
	if (!line)
	{
		elem.it_stat = it_err;
		return (elem);
	}
	getc_elem = next(iter->getc_iter);
	if (getc_elem.it_stat == it_end)
	{
		str_del(line);
		elem.it_stat = it_end;
		return (elem);
	}
	while (getc_elem.it_stat == it_ok)
	{
		if (*(char *)getc_elem.data == '\n')
		{
			if (!str_add(line, *(char *)getc_elem.data))
			{
				str_del(line);
				elem.it_stat = it_err;
				return (elem);
			}
			elem.data = line;
			elem.it_stat = it_ok;
			return (elem);
		}
		else if (!str_add(line, *(char *)getc_elem.data))
		{
			str_del(line);
			elem.it_stat = it_err;
			return (elem);
		}
		getc_elem = next(iter->getc_iter);
	}
	if (getc_elem.it_stat == it_end)
	{
		elem.data = line;
		elem.it_stat = it_ok;
		return (elem);
	}
	str_del(line);
	elem.it_stat = it_err;
	return (elem);
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

char	*get_next_line(int fd)
{
	static t_gnl_iter	*iter = NULL;
	t_elem				elem;
	t_str				*line;
	char				*ret;

	if (!iter)
	{
		iter = gnl_iter(fd);
		if (!iter)
			return (NULL);
	}
	elem = next(iter);
	if (elem.it_stat == it_ok)
	{
		line = (t_str *)elem.data;
		ret = strdup(line->_str);
		str_del(line);
		if (!ret)
			return (NULL);
		return (ret);
	}
	else
	{
		del_iter(iter);
		iter = NULL;
		return (NULL);
	}
}
