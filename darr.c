#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "darr.h"

t_darr	*darr_new(size_t nmemb, void (*del)(void *))
{
	t_darr	*darr;
	size_t	cap;

	darr = (t_darr *)malloc(sizeof(t_darr));
	if (!darr)
		return (NULL);
	cap = nmemb;
	if (cap == 0)
		cap = 1;
	darr->_arr = calloc(cap, sizeof(void *));
	if (!darr->_arr)
	{
		free(darr);
		return (NULL);
	}
	darr->_cap = cap;
	darr->_len = nmemb;
	darr->_del = del;
	return (darr);
}

void	darr_del(t_darr *darr)
{
	size_t	i;

	if (!darr)
		return ;
	i = 0;
	while (i < darr->_len)
	{
		if (darr->_del)
			darr->_del(darr->_arr[i]);
		i++;
	}
	free(darr->_arr);
	free(darr);
}

size_t	darr_len(t_darr *darr)
{
	return (darr->_len);
}

void	darr_set(t_darr *darr, size_t index, void *data)
{
	darr->_arr[index] = data;
}

void	*darr_get(t_darr *darr, size_t index)
{
	return (darr->_arr[index]);
}

bool	darr_resize(t_darr *darr, size_t new_cap)
{
	void	*new_arr;

	if (new_cap <= darr->_cap)
		return (true);
	new_arr = calloc(new_cap, sizeof(void *));
	if (!new_arr)
		return (false);
	memcpy(new_arr, darr->_arr, darr->_cap * sizeof(void *));
	free(darr->_arr);
	darr->_arr = new_arr;
	darr->_cap = new_cap;
	return (true);
}

bool	darr_add(t_darr *darr, void *data)
{
	if (darr->_len == darr->_cap && !darr_resize(darr, darr->_cap * 2))
		return (false);
	darr_set(darr, darr->_len, data);
	darr->_len++;
	return (true);
}

void	darr_set_del(t_darr *darr, void (*del)(void *))
{
	darr->_del = del;
}
