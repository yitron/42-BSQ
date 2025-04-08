/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:49:28 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 04:28:11 by huvu             ###   ########.fr       */
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
t_map_info	*init_map_info(char *buff, int *next_line_index)
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
	if (i == 0 || map_info->lines == 0 || !is_valid_map_char(buff[i]))
	{
		free(map_info);
		return (NULL);
	}
	if (buff[i] && is_valid_map_char(buff[i]))
		map_info->empty_char = buff[i++];
	if (buff[i] && is_valid_map_char(buff[i]))
		map_info->obstacle = buff[i++];
	if (buff[i] && is_valid_map_char(buff[i]))
		map_info->player = buff[i++];
	skip_to_next_line(buff, &i);
	*next_line_index = i;
	map_info->width = calculate_map_width(buff, i);
	return (map_info);
}

char	*copy_line(char *start, t_map_info map_info)
{
	char	*line;
	size_t	i;

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

char	**parse_map(char *str, int from, t_map_info map_info)
{
	size_t	i;
	size_t	len;
	char	**map;
	char	*start;

	map = (char **)malloc(sizeof(char *) * (map_info.lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	start = str + from;
	while (i < map_info.lines)
	{
		map[i] = copy_line(start, map_info);
		if (!map[i])
		{
			free(map);
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

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}
