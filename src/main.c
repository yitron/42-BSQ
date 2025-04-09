/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:09:54 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 15:50:01 by lhongzhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq/bsq.h"
#include "input/map_parser.h"
#include "input/map_reader.h"
#include "input/stdin_reader.h"
#include "utils/string_utils.h"
#include "utils/map_utils.h"

static int	process_map(char *map_input)
{
	char		**parsed_map;
	t_map_info	map_info;
	t_point		point_found;
	int			max;

	if (!init_map_info(map_input, &map_info))
		return (0);
	if (!is_valid_map_info(map_info))
		return (0);
	parsed_map = parse_map(map_input, map_info);
	if (!parsed_map)
	{
		free_map(parsed_map, map_info.lines);
		return (0);
	}
	max = find_maximal_square(parsed_map, &point_found, map_info);
	draw_square(parsed_map, point_found, max, map_info);
	free_map(parsed_map, map_info.lines);
	return (1);
}

static void	process_stdin(void)
{
	char	*buff;
	int		read_ok;

	buff = malloc(MAX_INPUT_SIZE);
	if (!buff)
	{
		ft_putstr("map error\n");
		return ;
	}
	read_ok = read_stdin_into_buffer(buff);
	if (!read_ok || buff[0] == '\0' || !process_map(buff))
		ft_putstr("map error\n");
	free(buff);
	return ;
}

static void	process_files(int argc, char **argv)
{
	char	*buff;
	int		i;

	i = 1;
	while (i < argc)
	{
		buff = read_file_to_string(argv[i]);
		if (!buff || buff[0] == '\0' || !process_map(buff))
			ft_putstr("map error\n");
		if (i < argc - 1)
			ft_put_char('\n');
		free(buff);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		process_stdin();
	}
	else
	{
		process_files(argc, argv);
	}
	return (0);
}
