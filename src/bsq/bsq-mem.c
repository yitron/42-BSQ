/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq-mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvu <huvu@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:14:08 by huvu              #+#    #+#             */
/*   Updated: 2025/04/09 10:09:00 by huvu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_map_cache(int **cache, int size)
{
	(void)size;
	if (!cache)
		return ;
	free(cache[0]);
	free(cache);
}

void	free_map(char **map, int size)
{
	(void)size;
	if (!map)
		return ;
	free(map[0]);
	free(map);
}

int	**init_map_cache(int lines, int width)
{
	int	**cache;
	int	*data;
	int	i;
	int	total_size;

	total_size = (lines + 1) * (width + 1);
	data = calloc(total_size, sizeof(int));
	if (!data)
		return (NULL);
	cache = malloc(sizeof(int *) * (lines + 1));
	if (!cache)
	{
		free(data);
		return (NULL);
	}
	i = 0;
	while (i <= lines)
	{
		cache[i] = data + (i * (width + 1));
		i++;
	}
	return (cache);
}
