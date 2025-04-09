/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:06:33 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 13:35:03 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H
# include <stdlib.h>
# include "../bsq/map.h"

typedef struct s_parse_vars
{
	char	*data_buffer;
	char	**map;
	char	*start;
	char	*dest;
	char	*str;
	int		i;
}	t_parse_vars;

int			init_map_info(char *buff, t_map_info *map_info);
int			allocate_memory(t_map_info map_info, t_parse_vars *vars);
char		**parse_map_lines(t_map_info map_info, t_parse_vars *vars);
char		**parse_map(char *str, t_map_info map_info);
void		free_map(char **map, int size);

void		init_parse_variables(char *str, t_map_info map_info,
				t_parse_vars *vars);
int			check_and_copy_line(t_map_info map_info, t_parse_vars *vars);
void		update_pointers(t_map_info map_info, t_parse_vars *vars);
char		*copy_line(char *start, t_map_info map_info);

#endif
