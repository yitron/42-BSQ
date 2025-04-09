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

int	allocate_memory(t_map_info map_info, t_parse_vars *vars)
{
	vars->data_buffer = malloc(sizeof(char) * (map_info.width + 1) 
			* map_info.lines);
	if (!vars->data_buffer)
		return (0);
	vars->map = malloc(sizeof(char *) * (map_info.lines + 1));
	if (!vars->map)
	{
		free(vars->data_buffer);
		return (0);
	}
	return (1);
}

char	**parse_map_lines(t_map_info map_info, t_parse_vars *vars)
{
	init_parse_variables(vars->str, map_info, vars);
	while (vars->i < map_info.lines)
	{
		vars->map[vars->i] = vars->dest;
		if (!check_and_copy_line(map_info, vars))
		{
			free(vars->data_buffer);
			free(vars->map);
			return (NULL);
		}
		update_pointers(map_info, vars);
		vars->i++;
	}
	vars->map[vars->i] = NULL;
	return (vars->map);
}

char	**parse_map(char *str, t_map_info map_info)
{
	t_parse_vars	vars;

	vars.str = str;
	if (!allocate_memory(map_info, &vars))
		return (NULL);
	return (parse_map_lines(map_info, &vars));
}