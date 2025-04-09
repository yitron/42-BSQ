/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:45:24 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 15:45:18 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "map_parser.h"
#include "../utils/map_utils.h"
#include "../utils/string_utils.h"

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

void	init_parse_variables(char *str, t_map_info map_info,
		t_parse_vars *vars)
{
	vars->start = str + map_info.first_row_index;
	vars->dest = vars->data_buffer;
	vars->i = 0;
}

int	check_and_copy_line(t_map_info map_info, t_parse_vars *vars)
{
	int	j;

	j = 0;
	while (j < map_info.width)
	{
		if (vars->start[j] != map_info.empty_char
			&& vars->start[j] != map_info.obstacle)
			return (0);
		vars->dest[j] = vars->start[j];
		j++;
	}
	vars->dest[j] = '\0';
	return (1);
}

void	update_pointers(t_map_info map_info, t_parse_vars *vars)
{
	vars->dest += map_info.width + 1;
	vars->start += map_info.width;
	if (vars->start[0] == '\n')
		vars->start++;
}