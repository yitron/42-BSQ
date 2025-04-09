/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:49:28 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 13:34:51 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "map_parser.h"
#include "../utils/map_utils.h"
#include "../utils/string_utils.h"

int	init_map_info(char *buff, t_map_info *map_info)
{
	size_t		i;

	i = 0;
	map_info->lines = 0;
	while (buff[i] && is_digit(buff[i]))
		map_info->lines = map_info->lines * 10 + (buff[i++] - '0');
	if (map_info->lines == 0 || !is_valid_map_char(buff[i])
		|| !is_valid_map_char(buff[i + 1]) || !is_valid_map_char(buff[i + 2]))
	{
		free(map_info);
		return (0);
	}
	map_info->empty_char = buff[i++];
	map_info->obstacle = buff[i++];
	map_info->player = buff[i++];
	skip_to_next_line(buff, &i);
	map_info->first_row_index = i;
	map_info->width = calculate_map_width(buff, i);
	return (1);
}

char	*copy_line(char *start, t_map_info map_info)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (map_info.width + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < map_info.width)
	{
		if (start[i] != map_info.empty_char && start[i] != map_info.obstacle)
		{
			free(line);
			return (NULL);
		}
		line[i] = start[i];
		i++;
	}
	if (i < map_info.width || start[i] != '\n')
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

char	**parse_map(char *str, t_map_info map_info)
{
	int		i;
	int		j;
	char	**map;
	char	*data_buffer;
	char	*start;
	char	*dest;

	data_buffer = malloc(sizeof(char) * map_info.width * map_info.lines + map_info.lines);
	if (!data_buffer)
		return (NULL);
	map = malloc(sizeof(char *) * (map_info.lines + 1));
	if (!map)
	{
		free(data_buffer);
		return (NULL);
	}
	start = str + map_info.first_row_index;
	dest = data_buffer;
	i = 0;
	while (i < map_info.lines)
	{
		map[i] = dest;
		j = 0;
		while (j < map_info.width)
		{
			if (start[j] != map_info.empty_char && start[j] != map_info.obstacle)
			{
				free(data_buffer);
				free(map);
				return (NULL);
			}
			dest[j] = start[j];
			j++;
		}
		dest[j] = '\0';
		dest += map_info.width + 1;
		start += map_info.width;
		if (start[0] == '\n')
			start++;
		i++;
	}
	map[i] = NULL;
	return (map);
}
