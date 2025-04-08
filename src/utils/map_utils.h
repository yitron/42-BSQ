/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:49:38 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 04:01:39 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H
# include "../bsq/bsq.h"

int	is_valid_map_char(char c);
int	is_valid_map_info(t_map_info *map_info);
int	is_digit(char c);

#endif