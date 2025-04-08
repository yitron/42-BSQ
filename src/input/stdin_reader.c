/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:31:32 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 03:54:13 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdin_reader.h"

int	read_stdin_into_buffer(char *buffer)
{
	char	temp[BUF_SIZE];
	ssize_t	bytes_read;
	size_t	offset;
	size_t	i;

	if (!buffer)
		return (0);
	offset = 0;
	bytes_read = read(0, temp, BUF_SIZE);
	while (bytes_read > 0)
	{
		i = 0;
		while (i < (size_t)bytes_read && offset < MAX_INPUT_SIZE - 1)
			buffer[offset++] = temp[i++];
		if (offset >= MAX_INPUT_SIZE - 1)
		{
			buffer[offset] = '\0';
			return (0);
		}
		bytes_read = read(0, temp, BUF_SIZE);
	}
	if (bytes_read == -1)
		return (0);
	buffer[offset] = '\0';
	return (1);
}
