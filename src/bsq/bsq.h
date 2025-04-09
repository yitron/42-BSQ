/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 04:04:48 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 10:07:00 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H
# define MAX_INPUT_SIZE 100000
# include "map.h"

typedef struct s_block_args
{
	t_point		block;
	t_point		*found;
	int			*max;
	t_map_info	*info;
}	t_block_args;

void	set_cache_and_max(int **cache, t_point *found, int *max, t_point p);
int		find_maximal_square(char **map, t_point *found, t_map_info map_info);
void	get_boundaries(t_point block, t_map_info *info, int *end_i, int *end_j);
void	init_args(t_block_args *args, t_point *found, int *max, 
		t_map_info *map_info);
void	process_map(char **map, int **cache, t_block_args *args);
void	scan_blocks(char **map, int **cache, t_block_args *args,
		t_map_info *map_info);
int		in_square(t_point start_point, int size, t_point current_point);
void	fill_buffer(char **map, t_point found, int size, char *buffer,
			t_map_info map_info, int *pos);
void	draw_square(char **map, t_point found, int size, t_map_info map_info);
void	free_map_cache(int **cache, int size);
void	free_map(char **map, int size);
int		**init_map_cache(int lines, int width);

#endif