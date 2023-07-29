/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:59:05 by clballes          #+#    #+#             */
/*   Updated: 2023/07/24 19:59:06 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	max_cols(t_map *map)
{
	int i;
	int j;

	j = 0;
	i = 0;
	map->cols = 0;
	while (map->map_arr[i])
	{
		while (map->map_arr[i][j])
			j++;
		if (map->cols < j)
			map->cols = j;
		j = 0;
		i++;
	}
}

void	handle_sp(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_arr[i])
	{
		j = 0;
		while (map->map_arr[i][j])
		{
			if (map->map_arr[i][j] == 32)
				map->map_arr[i][j] = '0';
			j++;
		}
		i++;
	}
}

int	ft_check_map(t_map *map, t_element *element)
{
	if (search_pos(map) != 0)
	{
		printf("error more letters or position\n");
		free_all(map, element, 1);
		return (1);
	}
	init_delta(map);
	copy_map(map);
	if (backtrack(map->copy_map, map->pos_y, map->pos_x, map) != 0)
	{
		printf("error map not sourrended by walls\n");
		free_all(map, element, 0);
		return (1);
	}
	free_arr(map->copy_map, map->rows);
	return (0);
}

void	ft_map_array(t_map *map, int fd)
{
	char	*line;
	int		i;

	i = 0;
	map->map_unid = NULL;
	line = get_next_line(fd);
	while (line)
	{
		while (ft_strlen(line) == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		if (!map->map_unid)
			map->map_unid = ft_strdup(line);
		else
			map->map_unid = free_var(map->map_unid, line);
		map->map_unid = free_var(map->map_unid, "\n");
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map->rows = i;
	map->map_arr = ft_split(map->map_unid, '\n');
	free(map->map_unid);
}

int	init_map(t_element *element, int fd)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		return(1);
	ft_map_array(map, fd);
	max_cols(map);
	handle_sp(map);
	if (ft_check_map(map, element) != 0)
		return (1);
	return (0);
}
