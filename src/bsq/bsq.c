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

void	set_cache_and_max(int **cache, t_point *found, int *max, t_point p)
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
	int			**cache;
	int			max;
	t_block_args	args;

	cache = init_map_cache(map_info.lines, map_info.width);
	if (!cache)
		return (0);
	max = 0;
	init_args(&args, found, &max, &map_info);
	scan_blocks(map, cache, &args, &map_info);
	free_map_cache(cache, map_info.lines + 1);
	return (max);
}