/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:49:28 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 12:33:51 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "map_parser.h"
#include "../utils/map_utils.h"
#include "../utils/string_utils.h"

// get map infor from the first line of the map
// the first line of the map should be in the format:
// <number_of_lines><empty_char><obstacle><player>
// then move the pointer to the next line
t_map_info	*init_map_info(char *buff)
{
	t_map_info	*map_info;
	size_t		i;

	map_info = malloc(sizeof(t_map_info));
	if (!map_info)
		return (NULL);
	i = 0;
	map_info->lines = 0;
	while (buff[i] && is_digit(buff[i]))
		map_info->lines = map_info->lines * 10 + (buff[i++] - '0');
	if (map_info->lines == 0 || !is_valid_map_char(buff[i])
		|| !is_valid_map_char(buff[i + 1]) || !is_valid_map_char(buff[i + 2]))
	{
		free(map_info);
		return (NULL);
	}
	map_info->empty_char = buff[i++];
	map_info->obstacle = buff[i++];
	map_info->player = buff[i++];
	skip_to_next_line(buff, &i);
	map_info->first_row_index = i;
	map_info->width = calculate_map_width(buff, i);
	return (map_info);
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
	char	**map;
	char	*start;

	map = (char **)malloc(sizeof(char *) * (map_info.lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	start = str + map_info.first_row_index;
	while (i < map_info.lines)
	{
		map[i] = copy_line(start, map_info);
		if (!map[i])
		{
			free_map(map, i);
			return (NULL);
		}
		start += map_info.width;
		if (start[0] == '\n')
			start++;
		i++;
	}
	map[i] = NULL;
	return (map);
}
