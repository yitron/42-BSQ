/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:15:24 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 04:13:20 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bsq.h"
#include "../utils/string_utils.h"
#include <stdio.h>

static int	min(int a, int b, int c)
{
	int	min;

	min = a;
	if (min > b)
		min = b;
	if (min > c)
		min = c;
	return (min);
}

static void	set_cache_and_max(int **cache, t_point *found, int *max, t_point p)
{
	int		min_val;

	min_val = min(cache[p.x][p.y + 1], cache[p.x + 1][p.y], cache[p.x][p.y]);
	cache[p.x + 1][p.y + 1] = min_val + 1;
	if (cache[p.x + 1][p.y + 1] > *max)
	{
		*max = cache[p.x + 1][p.y + 1];
		found->x = p.x - (*max) + 1;
		found->y = p.y - (*max) + 1;
	}
}

int	find_maximal_square(char **map, t_point *found, t_map_info map_info)
{
	int	**cache;
	int	max;
	int	i;
	int	j;

	cache = init_map_cache(map_info.lines, map_info.width);
	if (!cache)
		return (0);
	max = 0;
	i = 0;
	while (i < map_info.lines)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (map[i][j] == map_info.empty_char)
				set_cache_and_max(cache, found, &max, (t_point){i, j});
			j++;
		}
		i++;
	}
	free_map_cache(cache, i);
	return (max);
}

int	in_square(t_point start_point, int size, t_point current_point)
{
	if (current_point.x < start_point.x)
		return (0);
	if (current_point.x >= start_point.x + size)
		return (0);
	if (current_point.y < start_point.y)
		return (0);
	if (current_point.y >= start_point.y + size)
		return (0);
	return (1);
}

void	draw_square(char **map, t_point found, int size, t_map_info map_info)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_info.lines)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (in_square(found, size, (t_point){i, j}))
				ft_put_char(map_info.player);
			else
				ft_put_char(map[i][j]);
			j++;
		}
		ft_put_char('\n');
		i++;
	}
}
