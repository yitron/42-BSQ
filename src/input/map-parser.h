/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:06:33 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 22:01:18 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
#define MAP_PARSER_H
#include <stdlib.h>
#include "../bsq/map.h"

t_map_info	*init_map_info(char *map_file_content, int *next_line_index);
size_t	count_lines(char *str);
char	*copy_line(char *start, size_t length);
char	**split_lines(char *str, int from, int line_count);
void	free_map(char **map);
int		is_map_valid(char **map);

#endif
