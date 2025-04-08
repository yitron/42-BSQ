/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:06:33 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 10:01:40 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
#define MAP_PARSER_H
#include <stdlib.h>

typedef struct	s_map_info
{
	int		lines;
	char	empty_char;
	char	obstacle_char;
	char	player_char;
}	t_map_info;

t_map_info	*init_map_info(char *map_file_content);
size_t	count_lines(char *str);
char	*copy_line(char *start, size_t length);
char	**split_lines(char *str);
void	free_map(char **map);
int		is_map_valid(char **map);

#endif
