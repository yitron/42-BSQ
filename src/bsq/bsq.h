#ifndef BQS_H
# define BQS_H
# include "map.h"

void	free_map_cache(int **cache, int size);
int	**init_map_cache(int lines, int width);
int find_maximal_square(char **map, t_point *found, t_map_info map_info);
void draw_square(char **map, t_point found, int size, t_map_info map_info);

#endif