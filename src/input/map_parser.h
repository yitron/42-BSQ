/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:06:33 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 10:34:51 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H
# include <stdlib.h>
# include "../bsq/map.h"

t_map_info	*init_map_info(char *buff);
char		*copy_line(char *start, t_map_info map_info);
char		**parse_map(char *str, t_map_info map_info);
void		free_map(char **map, int size);

#endif
