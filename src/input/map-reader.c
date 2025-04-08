/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:43:10 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 09:23:10 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file implements map reader functions to read and validate a map
 * from a file. The map is stored as a 2D character array, where each
 * character represents a tile. The file must meet the following criteria:
 * - Correct format with specified rows and columns.
 * - Surrounded by walls with valid player, exit, and collectible tiles.
 * - Rectangular with no empty lines or spaces.
 * - Contains no invalid characters or out-of-bounds coordinates.
 * - Fully enclosed with no open edges or gaps.
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../utils/string_utils.h"

#define BUF_SIZE 1024

size_t	get_file_size(char *filename)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer[BUF_SIZE];
	size_t	total;

	total = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	bytes_read = read(fd, buffer, BUF_SIZE);
	while (bytes_read > 0)
	{
		total += (size_t)bytes_read;
		bytes_read = read(fd, buffer, BUF_SIZE);
	}
	close(fd);
	if (bytes_read == -1)
		return (0);
	return (total);
}

void	copy_to_buffer(char *buffer, char *temp, size_t *from, ssize_t total)
{
	size_t	i;

	i = 0;
	while (i < total)
	{
		buffer[*from] = temp[i];
		(*from)++;
		i++;
	}
}

int	read_file_into_buffer(char *filename, char *buffer)
{
	int		fd;
	ssize_t	bytes_read;
	size_t	offset;
	char	temp[BUF_SIZE];

	offset = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	bytes_read = read(fd, temp, BUF_SIZE);
	while (bytes_read > 0)
	{
		copy_to_buffer(buffer, temp, &offset, bytes_read);
		bytes_read = read(fd, temp, BUF_SIZE);
	}
	close(fd);
	if (bytes_read == -1)
		return (0);
	buffer[offset] = '\0';
	return (1);
}

char	*read_file_to_string(char *filename)
{
	char	*buffer;
	size_t	size;
	int		ok;

	size = get_file_size(filename);
	if (size == 0)
		return (NULL);
	buffer = (char *)malloc(size + 1);
	if (!buffer)
		return (NULL);
	ok = read_file_into_buffer(filename, buffer);
	if (!ok)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
