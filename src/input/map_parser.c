/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:49:28 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 04:18:31 by huvu             ###   ########.fr       */
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
t_map_info	*init_map_info(char *input_content, int *next_line_index)
{
	t_map_info	*map_info;
	size_t		i;

	map_info = malloc(sizeof(t_map_info));
	if (!map_info)
		return (NULL);
	i = 0;
	map_info->lines = 0;
	while (input_content[i] && is_digit(input_content[i]))
		map_info->lines = map_info->lines * 10 + (input_content[i++] - '0');
	if (i == 0 || map_info->lines == 0 || !is_valid_map_char(input_content[i]))
	{
		free(map_info);
		return (NULL);
	}
	if (input_content[i] && is_valid_map_char(input_content[i]))
		map_info->empty_char = input_content[i++];
	if (input_content[i] && is_valid_map_char(input_content[i]))
		map_info->obstacle = input_content[i++];
	if (input_content[i] && is_valid_map_char(input_content[i]))
		map_info->player = input_content[i++];
	while (input_content[i] && input_content[i] != '\n')
		i++;
	i++;
	*next_line_index = i;
	map_info->width = 0;
	while (input_content[i] && (input_content[i++] != '\n'))
		map_info->width++;
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

int	is_map_valid(char **map)
{
	size_t	i;
	size_t	j;
	size_t	line_length;
	size_t	expected_length;

	if (!map || !map[0])
		return (0);
	i = 0;
	expected_length = ft_strlen(map[0]);
	while (map[i])
	{
		line_length = ft_strlen(map[i]);
		if (line_length != expected_length)
			return (0);
		while (j < line_length)
		{
			if (map[i][j] != '.' && map[i][j] != 'o')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
