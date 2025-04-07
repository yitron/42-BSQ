/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:43:10 by huvu              #+#    #+#             */
/*   Updated: 2025/04/08 01:12:32 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * this file contains the implementation of the map reader functions.
 * it reads the map from a file and stores it in a 2D array.
 * it also checks for errors in the map format and contents.
 * the map is stored in a 2D array of characters, where each character
 * represents a tile in the map.
 * the map is read from a file specified by the user.
 * the file must be in the correct format, with the correct number of
 * rows and columns.
 * the map must also be surrounded by walls, and the player must be
 * represented by a valid character.
 * the map must also contain at least one exit and one collectible.
 * the map must also be rectangular, with no empty lines or spaces.
 * the map must also be valid, with no invalid characters or
 * out-of-bounds coordinates.
 * the map must also be closed, with no open edges or gaps.
 * the map must also be complete, with no missing tiles or
 * incomplete rows or columns.
 * the map must also be correct, with no incorrect tiles or
 * incorrect coordinates.
 */

#include <fcntl.h>	// For open
#include <unistd.h> // For read and close
#include <stdlib.h> // For malloc and free
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
