/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:15:24 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 12:53:18 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bsq.h"
#include "../utils/string_utils.h"
#include <stdio.h>

static void	set_cache_and_max(int **cache, t_point *found, int *max, t_point p)
{
	int		min;

	min = cache[p.x][p.y + 1];
	if (min > cache[p.x + 1][p.y])
		min = cache[p.x + 1][p.y];
	if (min > cache[p.x][p.y])
		min = cache[p.x][p.y];
	cache[p.x + 1][p.y + 1] = min + 1;
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
	free_map_cache(cache, map_info.lines + 1);
	return (max);
}

int	in_square(t_point start_point, int size, t_point current_point)
{
	return (current_point.x >= start_point.x
		&& current_point.x < start_point.x + size
		&& current_point.y >= start_point.y
		&& current_point.y < start_point.y + size);
}

void	draw_square(char **map, t_point found, int size, t_map_info map_info)
{
	char	*line_buffer;
	int		i;
	int		j;

	line_buffer = malloc(sizeof(char) * (map_info.width + 2));
	if (!line_buffer)
		return ;
	i = 0;
	while (i < map_info.lines)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (in_square(found, size, (t_point){i, j}))
				line_buffer[j] = map_info.player;
			else
				line_buffer[j] = map[i][j];
			j++;
		}
		line_buffer[j] = '\n';
		line_buffer[j + 1] = '\0';
		write(1, line_buffer, j + 1);
		i++;
	}
	free(line_buffer);
}
