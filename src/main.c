/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:09:54 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 22:48:41 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/bsq.h"
#include "input/map-parser.h"
#include "input/map-reader.h"
#include "utils/string_utils.h"

int	main(int argc, char **argv)
{
	char	*file_content;
	char	**parsed_map;
	int		next_line_index;

	if (argc != 2)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" <map_file>\n");
		return (1);
	}
	file_content = read_file_to_string(argv[1]);
	if (!file_content)
	{
		ft_putstr("Map error\n");
		return (1);
	}
	ft_putstr("Map file read successfully\n");
	ft_putstr(file_content);
	ft_putstr("\n\n");
	t_map_info	*map_info = init_map_info(file_content, &next_line_index);
	if (!map_info)
	{
		ft_putstr("Map error\n");
		free(file_content);
		return (1);
	}
	ft_putstr("Map info:\n");
	ft_putstr("Lines: ");
	ft_put_nbr(map_info->lines);
	ft_putstr("\nEmpty char: ");
	ft_put_char(map_info->empty_char);
	ft_putstr("\nObstacle char: ");
	ft_put_char(map_info->obstacle_char);
	ft_putstr("\nPlayer char: ");
	ft_put_char(map_info->player_char);
	ft_putstr("\n\n");
	parsed_map = split_lines(file_content, next_line_index + 1, map_info->lines);
	
	if (!parsed_map)
	{
		ft_putstr("Map error\n");
		free(file_content);
		return (1);
	}
	map_info->width = ft_strlen(parsed_map[0]);
	t_point *point = malloc(sizeof(t_point));
	int max = find_maximal_square(parsed_map, point, *map_info);

	ft_putstr("Max size found = ");
	ft_put_nbr(max);
	ft_putstr("\nAt x=");
	ft_put_nbr(point->x);
	ft_putstr("\nAt y=");
	ft_put_nbr(point->y);
	ft_putstr("Results: \n");
	draw_square_on_map(parsed_map, *point, max, *map_info);
	free(file_content);
	return (0);
}
