/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:19:10 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 10:34:11 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map_info
{
	int		lines;
	int		width;
	char	empty_char;
	char	obstacle;
	char	player;
	char	first_row_index;
}	t_map_info;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

#endif