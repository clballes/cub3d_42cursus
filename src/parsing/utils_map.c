#include "cub3d.h"

void	init_delta(t_map *map)
{
	int	delta_row[4];
	int	delta_col[4];
	int	i;

	delta_row[0] = -1;
	delta_row[1] = 0;
	delta_row[2] = 1;
	delta_row[3] = 0;
	delta_col[0] = 0;
	delta_col[1] = 1;
	delta_col[2] = 0;
	delta_col[3] = -1;
	i = 0;
	while (i < 4)
	{
		map->delta_row[i] = delta_row[i];
		map->delta_col[i] = delta_col[i];
		i++;
	}
}

void	copy_map(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	map->copy_map = malloc(sizeof(char *) * map->rows);
	if (map->copy_map == NULL)
		return ;
	while (i < map->rows)
	{
		map->copy_map[i] = ft_strdup(map->map_arr[i]);
		i++;
	}
}

void	free_arr(char **copy_map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(copy_map[i]);
		i++;
	}
	free(copy_map);
}

void	free_elements(t_element *element)
{
	int i;
	
	i = 0;
	while (i < 6)
	{
		free(element[i].direction);
		free(element[i].id);
		i++;
	}
	free(element);
}

void	free_all(t_map *map, int i)
{
	free_elements(map->element);
	if (i == 0)
		free_arr(map->copy_map, map->rows);
	free_arr(map->map_arr, map->rows);
	free(map);
}