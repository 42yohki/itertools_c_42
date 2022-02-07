#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "iter.h"
#include "elem.h"
#include "foreach.h"
#include "filter.h"
#include "map.h"
#include "reduce.h"
#include "range.h"
#include "darr.h"
#include "darr_iter.h"
#include "get_next_line.h"
#include "sort.h"

// filter
bool	is_x2(void *i)
{
	return (*(int *)i % 2 == 0);
}

// filter
bool	is_x3(void *i)
{
	return (*(int *)i % 3 == 0);
}

// map
void	*to_x2(void *i)
{
	int	*j;

	j = malloc(sizeof(int));
	if (!j)
		return (NULL);
	*j = *(int *)i * 2;
	return (j);
}

// callback
void	print_int(void *i)
{
	printf("%d\n", *(int *)i);
}

// reduce
void	*add(void *a, void *b)
{
	int	*sum;

	sum = malloc(sizeof(int));
	if (sum)
		*sum = *(int *)a + *(int *)b;
	return (sum);
}

// sort
int		cmp_int_desc(const void *a, const void *b)
{
	return (**(int **)b - **(int **)a);
}

void	example1(void)
{
	void	*it;

	printf("[Example 1]\n");
	foreach(({
			it = range(0, 100);
			it = filter(it, is_x2);
			it = filter(it, is_x3);
			it = map(it, to_x2, free);
			it = sort(it, &cmp_int_desc);
		}), print_int);
}

void	example2(void)
{
	t_darr	*darr;
	int		*sum;

	printf("[Example 2]\n");
	darr = darr_collect(range(0, 100));
	if (!darr)
		return ;
	sum = reduce(darr_iter(darr), add, calloc(1, sizeof(int)), free);
	if (!sum)
		return ;
	printf("sum = %d\n", *sum);
	darr_del(darr);
	free(sum);
}

// example3
void	example3(void)
{
	char	*line;

	printf("[Example 3]\n");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		printf("> %s", line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

int	main(void)
{
	example1();
	example2();
	example3();
	return (0);
}
