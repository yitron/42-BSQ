/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 04:04:48 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 14:46:56 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H
# include "map.h"

void	free_map_cache(int **cache, int size);
void	free_map(char **map, int size);
int		**init_map_cache(int lines, int width);
int		find_maximal_square(char **map, t_point *found, t_map_info map_info);
void	draw_square(char **map, t_point found, int size, t_map_info map_info);

#endif