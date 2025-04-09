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

static void	process_block(char **map, int **cache, t_point *found, 
				int *max, t_map_info map_info, t_point block)
{
	t_point	p;
	int		end_i;
	int		end_j;

	end_i = block.x + 64 < map_info.lines ? block.x + 64 : map_info.lines;
	end_j = block.y + 64 < map_info.width ? block.y + 64 : map_info.width;
	p.x = block.x - 1;
	while (++p.x < end_i)
	{
		p.y = block.y - 1;
		while (++p.y < end_j)
			if (map[p.x][p.y] == map_info.empty_char)
				set_cache_and_max(cache, found, max, p);
	}
}

int	find_maximal_square(char **map, t_point *found, t_map_info map_info)
{
	int		**cache;
	int		max;
	t_point	block;

	cache = init_map_cache(map_info.lines, map_info.width);
	if (!cache)
		return (0);
	max = 0;
	block.x = 0;
	while (block.x < map_info.lines)
	{
		block.y = 0;
		while (block.y < map_info.width)
		{
			process_block(map, cache, found, &max, map_info, block);
			block.y += 64;
		}
		block.x += 64;
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
	char	*buffer;
	int		i;
	int		j;
	int		pos;
	int		buffer_size;

	buffer_size = (map_info.width + 1) * map_info.lines;
	buffer = malloc(sizeof(char) * buffer_size);
	if (!buffer)
		return ;
	
	pos = 0;
	i = 0;
	while (i < map_info.lines)
	{
		j = 0;
		while (j < map_info.width)
		{
			if (i >= found.x && i < found.x + size && j >= found.y && j < found.y + size)
				buffer[pos++] = map_info.player;
			else
				buffer[pos++] = map[i][j];
			j++;
		}
		buffer[pos++] = '\n';
		i++;
	}
	
	write(1, buffer, pos);
	free(buffer);
}
