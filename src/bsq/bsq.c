/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:15:24 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 23:05:58 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "map.h"
#include "../utils/string_utils.h"
#include <stdio.h>

static void free_map_cache(int **cache, int size)
{
	int i;

	i = 0;
	while (i < size)
		free(cache[i++]);
	free(cache);
}

static int min_of(int a, int b, int c)
{
	int min;

	min = a;
	if (min > b)
		min = b;
	if (min > c)
		min = c;
	return (min);
}

static int max_of(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int find_maximal_square(char **map, t_point *found, t_map_info map_info)
{
	int **cache;
	int	max;
	int	i;
	int	j;

	cache = malloc(sizeof(int*) * (map_info.lines + 1));
	if (!cache)
		return 0;
	i = 0;
	// ft_putstr("reach here\n");
	while (i <= map_info.lines)
	{
		cache[i] = malloc(sizeof(int) * (map_info.width + 1));
		if (!cache[i])
		{
			free_map_cache(cache, i);
			return 0;
		}
		while (j <= map_info.width)
			cache[i][j++] = 0;
		i++;
	}
	max = 0;
	i = 0;
	found->x = 0;
	found->y = 0;
	while (i < map_info.lines)
	{
		j = 0;
		while (j < map_info.width)
		{
			// ft_put_char(map[i][j]);
			if (map[i][j] == map_info.empty_char)
			{
				cache[i + 1][j + 1] = min_of(cache[i][j + 1], cache[i + 1][j], cache[i][j]) + 1;
				if (cache[i + 1][j + 1] > max){
					max = cache[i + 1][j + 1];
					found->x = i;
					found->y = j;
					// printf("Found max at [%d, %d] with value=%d\n", i+1, j+1,max);
				}
			}
			j++;
		}
		i++;
	}
	return max;
}

void draw_square_on_map(char **map, t_point found, int size, t_map_info map_info)
{
	int i = 0;
	int j = 0;
	printf("Drawing from [%d,%d] backward for %d steps\n", i, j, size);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			map[found.x - i][found.y - j] = map_info.player_char;
			j++;
		}
		i++;
	}

	i = 0;
	
	while (i < map_info.lines)
	{
		ft_putstr(map[i++]);
		ft_put_char('\n');
	}
}