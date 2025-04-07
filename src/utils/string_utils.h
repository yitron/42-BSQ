/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:49:41 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 00:08:04 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H
# include <unistd.h>
# include <stdlib.h>

int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *str);
void	ft_strcat(char *dest, char *src);
int		ft_strlen(char *str);
void	ft_strcpy(char *dest, char *src);

#endif