#ifndef BQS_H
# define BQS_H
# include "map.h"

int find_maximal_square(char **map, t_point *found, t_map_info map_info);
void draw_square_on_map(char **map, t_point found, int size, t_map_info map_info);

#endif