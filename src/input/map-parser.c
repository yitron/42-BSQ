/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:49:28 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 18:12:22 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "map-parser.h"
#include "../utils/string_utils.h"

// get map infor from the first line of the map
// the first line of the map should be in the format:
// <number_of_lines><empty_char><obstacle_char><player_char>
// then move the pointer to the next line
t_map_info	*init_map_info(char *map_file_content, int *next_line_index)
{
	t_map_info	*map_info;
	size_t		i;

	map_info = malloc(sizeof(t_map_info));
	if (!map_info)
		return (NULL);
	i = 0;
	map_info->lines = 0;
	while (map_file_content[i] && map_file_content[i] >= '0' && map_file_content[i] <= '9')
	{
		map_info->lines = map_info->lines * 10 + (map_file_content[i] - '0');
		i++;
	}
	if (map_file_content[i])
		map_info->empty_char = map_file_content[i++];
	if (map_file_content[i])
		map_info->obstacle_char = map_file_content[i++];
	if (map_file_content[i])
		map_info->player_char = map_file_content[i++];
	// move the pointer to the next line
	while (map_file_content[i] && map_file_content[i] != '\n')
		i++;
	*next_line_index = i;
	return (map_info);
}

size_t	count_lines(char *str)
{
	size_t	lines;
	size_t	i;

	lines = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			lines++;
		i++;
	}
	if (str[i - 1] != '\n')
		lines++;
	return (lines);
}

char	*copy_line(char *start, size_t length)
{
	char	*line;
	size_t	i;

	line = malloc(sizeof(char) * (length + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < length)
	{
		line[i] = start[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**split_lines(char *str, int from, int line_count)
{
	size_t	lines;
	size_t	i;
	char	**map;
	char	*start;
	size_t	len;

	lines = count_lines(str);
	map = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	start = str + from;
	while (i < line_count)
	{
		len = 0;
		while (start[len] && start[len] != '\n')
			len++;
		map[i] = copy_line(start, len);
		if (!map[i])
		{
			free(map);
			return (NULL);
		}
		start += len;
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
