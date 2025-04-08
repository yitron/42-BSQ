/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_reader.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:08:34 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 02:09:11 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDIN_READER_H
# define STDIN_READER_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../bsq/bsq.h"

# define BUF_SIZE 1024
# define MAX_INPUT_SIZE 100000

int read_stdin_into_buffer(char *buffer);

#endif