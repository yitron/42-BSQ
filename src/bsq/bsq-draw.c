/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq-draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:30:24 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 15:30:18 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "bsq.h"

int	in_square(t_point start_point, int size, t_point current_point)
{
	return (current_point.x >= start_point.x
		&& current_point.x < start_point.x + size
		&& current_point.y >= start_point.y
		&& current_point.y < start_point.y + size);
}

static char	get_char_for_position(char **map, t_point found, int size,
				t_map_info map_info, int i, int j)
{
	if (i >= found.x && i < found.x + size
		&& j >= found.y && j < found.y + size)
		return (map_info.player);
	return (map[i][j]);
}

void	fill_buffer(char **map, t_point found, int size, char *buffer,
				t_map_info map_info, int *pos)
{
	int	i;
	int	j;

	i = -1;
	*pos = 0;
	while (++i < map_info.lines)
	{
		j = -1;
		while (++j < map_info.width)
		{
			buffer[(*pos)++] = get_char_for_position(map, found, size,
							map_info, i, j);
		}
		buffer[(*pos)++] = '\n';
	}
}

void	draw_square(char **map, t_point found, int size, t_map_info map_info)
{
	char	*buffer;
	int		buffer_size;
	int		pos;

	buffer_size = (map_info.width + 1) * map_info.lines;
	buffer = malloc(sizeof(char) * buffer_size);
	if (!buffer)
		return ;
	fill_buffer(map, found, size, buffer, map_info, &pos);
	write(1, buffer, pos);
	free(buffer);
}