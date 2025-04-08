/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq-mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:14:08 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 04:04:30 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_map_cache(int **cache, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(cache[i++]);
	free(cache);
}

int	**init_map_cache(int lines, int width)
{
	int	**cache;
	int	i;

	cache = malloc(sizeof(int *) * (lines + 1));
	if (!cache)
		return (NULL);
	i = 0;
	while (i <= lines)
	{
		cache[i] = malloc(sizeof(int) * (width + 1));
		if (!cache[i])
		{
			free_map_cache(cache, i);
			return (NULL);
		}
		i++;
	}
	return (cache);
}
