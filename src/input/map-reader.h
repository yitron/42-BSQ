/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:08:26 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 09:57:55 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_READER_H
# define MAP_READER_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../utils/string_utils.h"

size_t	get_file_size(char *filename);
int		read_file_into_buffer(char *filename, char *buffer);
char	*read_file_to_string(char *filename);
void	copy_to_buffer(char *buffer, char *temp, size_t *from, ssize_t total);

#endif