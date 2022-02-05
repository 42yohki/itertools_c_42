#ifndef STR_H
# define STR_H
# include <stddef.h>
# include <stdbool.h>

typedef struct s_str {
	char	*_str;
	size_t	_len;
	size_t	_cap;
}	t_str;

t_str	*str_new(void);
void	str_del(t_str *str);
size_t	str_len(t_str *str);
void	str_set(t_str *str, size_t index, char c);
char	str_get(t_str *str, size_t index);
bool	str_add(t_str *str, char c);
char	*str_c_str(t_str *str);

#endif
