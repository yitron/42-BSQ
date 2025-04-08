/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:09:54 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 10:03:11 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input/map-parser.h"
#include "input/map-reader.h"
#include "utils/string_utils.h"

int	main(int argc, char **argv)
{
	char	*file_content;
	char	**parsed_map;

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
	t_map_info	*map_info = init_map_info(file_content);
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
	parsed_map = split_lines(file_content);
	if (!parsed_map)
	{
		ft_putstr("Map error\n");
		free(file_content);
		return (1);
	}
	ft_putstr(parsed_map[0]);
	free(file_content);
	return (0);
}
