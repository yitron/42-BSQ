/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:09:54 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 04:49:34 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/bsq.h"
#include "input/map_parser.h"
#include "input/map_reader.h"
#include "input/stdin_reader.h"
#include "utils/string_utils.h"
#include "utils/map_utils.h"

static int	process_file(char *file_content)
{
	char		**parsed_map;
	int			next_line_index;
	t_map_info	*map_info;
	t_point		*point;
	int			max;

	if (!file_content)
		return (0);
	map_info = init_map_info(file_content, &next_line_index);
	if (is_valid_map_info(map_info) == 0)
	{
		free(file_content);
		return (1);
	}
	parsed_map = parse_map(file_content, next_line_index, *map_info);
	if (!parsed_map)
	{
		free(map_info);
		free(file_content);
		return (1);
	}
	map_info->width = ft_strlen(parsed_map[0]);
	point = malloc(sizeof(t_point));
	max = find_maximal_square(parsed_map, point, *map_info);
	draw_square(parsed_map, *point, max, *map_info);
	free(file_content);
	free_map(parsed_map);
	free(point);
	free(map_info);
	return (0);
}

static void	process_files(int argc, char **argv)
{
	char	*file_content;
	int		i;

	if (argc == 1)
	{
		file_content = malloc(MAX_INPUT_SIZE);
		if (!file_content)
		{
			ft_putstr("Memory allocation error\n");
			return ;
		}
		if (read_stdin_into_buffer(file_content) == 0)
		{
			ft_putstr("map error\n");
			free(file_content);
			return ;
		}
		if (file_content[0] == '\0' || process_file(file_content) != 0)
		{
			ft_putstr("map error\n");
		}
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			file_content = read_file_to_string(argv[i]);
			if (process_file(file_content) != 0)
			{
				ft_putstr("map error\n");
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	process_files(argc, argv);
	return (0);
}
