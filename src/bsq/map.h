/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:19:10 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 20:24:30 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct	s_map_info
{
	int		lines;
	int		width;
	char	empty_char;
	char	obstacle_char;
	char	player_char;
}	t_map_info;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

#endif