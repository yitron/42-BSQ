/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 00:49:28 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 01:06:16 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

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

char	**split_lines(char *str)
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
	start = str;
	while (i < lines)
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
	expected_length = strlen(map[0]);
	while (map[i])
	{
		line_length = strlen(map[i]);
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
