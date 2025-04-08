/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:48:10 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 04:13:47 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_utils.h"
#include "string_utils.h"

int	is_valid_map_char(char c)
{
	if (c == '\n' || c == '\r' || c == ' ' || c == '\t' || c == '\0')
		return (0);
	return (1);
}

void	print_map_info(t_map_info *map_info)
{
	if (!map_info)
		return ;
	ft_putstr("Map info:\n");
	ft_putstr("Lines: ");
	ft_put_nbr(map_info->lines);
	ft_putstr("\nWidth: ");
	ft_put_nbr(map_info->width);
	ft_putstr("\nEmpty char: ");
	ft_put_char(map_info->empty_char);
	ft_putstr("\nObstacle char: ");
	ft_put_char(map_info->obstacle);
	ft_putstr("\nPlayer char: ");
	ft_put_char(map_info->player);
	ft_putstr("\n");
}

int	is_valid_map_info(t_map_info *map_info)
{
	if (!map_info)
		return (0);
	if (map_info->lines <= 0 || map_info->width <= 0)
		return (0);
	if (is_valid_map_char(map_info->empty_char) == 0)
		return (0);
	if (is_valid_map_char(map_info->obstacle) == 0)
		return (0);
	if (is_valid_map_char(map_info->player) == 0)
		return (0);
	if (map_info->empty_char == map_info->obstacle)
		return (0);
	if (map_info->empty_char == map_info->player)
		return (0);
	if (map_info->obstacle == map_info->player)
		return (0);
	return (1);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
