/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_reader.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:08:34 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 15:02:17 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDIN_READER_H
# define STDIN_READER_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../bsq/bsq.h"

# define BUF_SIZE 1024

char	*read_stdin_into_buffer(void);

#endif