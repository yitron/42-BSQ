/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:35:24 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 15:35:18 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bsq.h"

void	get_boundaries(t_point block, t_map_info *info,
		int *end_i, int *end_j)
{
	if (block.x + 64 < info->lines)
		*end_i = block.x + 64;
	else
		*end_i = info->lines;
	if (block.y + 64 < info->width)
		*end_j = block.y + 64;
	else
		*end_j = info->width;
}

void	init_args(t_block_args *args, t_point *found,
		int *max, t_map_info *map_info)
{
	args->found = found;
	args->max = max;
	args->info = map_info;
}

void	process_map(char **map, int **cache, t_block_args *args)
{
	t_point	p;
	int		end_i;
	int		end_j;

	get_boundaries(args->block, args->info, &end_i, &end_j);
	p.x = args->block.x - 1;
	while (++p.x < end_i)
	{
		p.y = args->block.y - 1;
		while (++p.y < end_j)
			if (map[p.x][p.y] == args->info->empty_char)
				set_cache_and_max(cache, args->found, args->max, p);
	}
}

void	scan_blocks(char **map, int **cache, t_block_args *args,
		t_map_info *map_info)
{
	t_point	block;

	block.x = 0;
	while (block.x < map_info->lines)
	{
		block.y = 0;
		while (block.y < map_info->width)
		{
			args->block = block;
			process_map(map, cache, args);
			block.y += 64;
		}
		block.x += 64;
	}
}