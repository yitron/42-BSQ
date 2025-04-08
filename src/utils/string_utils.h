/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:49:41 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 04:32:09 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H
# include <unistd.h>
# include <stdlib.h>

void	ft_put_nbr(int n);
void	ft_put_char(char c);
void	ft_putstr(char *str);
int		ft_strlen(char *str);
int		is_digit(char c);

#endif