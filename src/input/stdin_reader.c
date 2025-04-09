/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:31:32 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 15:16:17 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdin_reader.h"

static char	*resize_buffer(char *buff, ssize_t *buff_size, ssize_t offset)
{
	char	*new_buff;
	ssize_t	i;

	new_buff = malloc(*buff_size * 2);
	if (!new_buff)
	{
		free(buff);
		return (NULL);
	}
	i = 0;
	while (i < offset)
	{
		new_buff[i] = buff[i];
		i++;
	}
	free(buff);
	*buff_size *= 2;
	return (new_buff);
}

void	append_to_buffer(char *buff, char *temp, ssize_t count, ssize_t *offset)
{
	ssize_t	i;

	i = 0;
	while (i < count)
		buff[(*offset)++] = temp[i++];
}

char	*read_stdin_into_buffer(void)
{
	char	*buff;
	char	temp[BUF_SIZE];
	ssize_t	buff_size;
	ssize_t	bytes_read;
	ssize_t	offset;

	buff_size = BUF_SIZE;
	buff = malloc(buff_size);
	if (!buff)
		return (NULL);
	offset = 0;
	bytes_read = read(0, temp, BUF_SIZE);
	while (bytes_read > 0)
	{
		if (offset + bytes_read >= buff_size)
		{
			buff = resize_buffer(buff, &buff_size, offset);
			if (!buff)
				return (NULL);
		}
		append_to_buffer(buff, temp, bytes_read, &offset);
		bytes_read = read(0, temp, BUF_SIZE);
	}
	buff[offset] = '\0';
	return (buff);
}
