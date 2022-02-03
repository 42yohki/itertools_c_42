#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iter.h"
#include "elem.h"
#include "foreach.h"
#include "filter.h"
#include "map.h"
#include "reduce.h"
#include "range.h"
#include "darr.h"
#include "darr_iter.h"

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
void	map_x2(void *i)
{
	*(int *)i *= 2;
}

// new_map
void	*map_cpy(void *i)
{
	int	*new_i;

	new_i = malloc(sizeof(int));
	if (!new_i)
		return (NULL);
	*new_i = *(int *)i;
	return (new_i);
}

// callback
void	print_int(void *i)
{
	printf("%d\n", *(int *)i);
}

// reduce
void	*sum_int(void *prev, void *curr)
{
	*(int *)prev += *(int *)curr;
	return (prev);
}

void	example1(void)
{
	printf("[Example 1]\n");
	foreach(
		map_iter(
			new_map_iter(
				filter_iter(
					filter_iter(
						range_iter(0, 100),
						is_x2),
					is_x3),
				map_cpy,
				free),
			map_x2),
		print_int);
}

void	example2(void)
{
	t_darr	*darr;
	int		sum;

	printf("[Example 2]\n");
	darr = reduce_iter(
		new_map_iter(
			range_iter(0, 100),
			map_cpy,
			NULL),
		collect_darr,
		darr_new(0, free),
		(t_del_sum)darr_del);
	if (!darr)
		return ;
	sum = 0;
	reduce_iter(
		get_darr_iter(darr),
		sum_int,
		&sum,
		NULL);
	printf("sum = %d\n", sum);
	darr_del(darr);
}

int	main(void)
{
	example1();
	example2();
	return (0);
}
