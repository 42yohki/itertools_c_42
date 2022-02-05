#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "str.h"

t_str	*str_new(void)
{
	t_str	*str;
	
	str = (t_str *)malloc(sizeof(t_str));
	if (!str)
		return (NULL);
	str->_str = calloc(1, sizeof(char));
	if (!str->_str)
	{
		free(str);
		return (NULL);
	}
	str->_cap = 1;
	str->_len = 0;
	return (str);
}

void	str_del(t_str *str)
{
	if (!str)
		return ;
	free(str->_str);
	free(str);
}

size_t	str_len(t_str *str)
{
	return (str->_len);
}

void	str_set(t_str *str, size_t index, char c)
{
	str->_str[index] = c;
}

char	str_get(t_str *str, size_t index)
{
	return (str->_str[index]);
}

bool	str_resize(t_str *str, size_t new_cap)
{
	char	*new_str;

	if (new_cap <= str->_cap)
		return (true);
	new_str = calloc(new_cap, sizeof(char));
	if (!new_str)
		return (false);
	memcpy(new_str, str->_str, str->_cap * sizeof(char));
	free(str->_str);
	str->_str = new_str;
	str->_cap = new_cap;
	return (true);
}

bool	str_add(t_str *str, char c)
{
	if (str->_len + 1 == str->_cap && !str_resize(str, str->_cap * 2))
		return (false);
	str_set(str, str->_len, c);
	str->_len++;
	return (true);
}

char	*str_c_str(t_str *str)
{
	return (strdup(str->_str));
}
