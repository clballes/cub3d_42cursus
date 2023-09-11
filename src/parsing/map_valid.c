/* ************************************************************************** */
/*	                                                                         */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:46:49 by clballes          #+#    #+#             */
/*   Updated: 2023/07/27 12:46:51 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_move_valid(char **map_arr, int row, int col)
{
	return (map_arr[row][col] != '1' && (row >= 0) && (col >= 0));
}

int	backtrack(char **map_arr, int row, int col, t_map *map)
{
	int			i;
	static char	c = 'V';

	i = -1;
	if (map_arr[row][col] != '1')
		map_arr[row][col] = c;
	while (++i < 4)
	{
		map->next_row = row + map->delta_row[i];
		map->next_col = col + map->delta_col[i];
		if (map->next_row < 0 || map->next_col < 0
			|| map->next_row >= map->rows || map->next_col >= map->cols)
			return (1);
		if (is_move_valid(map_arr, map->next_row, map->next_col)
			&& map_arr[map->next_row][map->next_col] != c)
		{
			if (backtrack(map_arr, map->next_row, map->next_col, map))
				return (1);
		}
	}
	return (0);
}

int	check_letter(t_map *map, int i, int j)
{
	if (map->map_arr[i][j] == 'S' || map->map_arr[i][j] == 'W'
		|| map->map_arr[i][j] == 'E' || map->map_arr[i][j] == 'N')
	{
		map->player_orientation = map->map_arr[i][j];
		map->pos_x = j;
		map->pos_y = i;
		return (0);
	}
	else
		return (1);
}

int	search_pos(t_map *map)
{
	int	i;
	int	check;
	int	j;

	i = 0;
	j = 0;
	check = -1;
	while (map->map_arr[i])
	{
		j = 0;
		while (map->map_arr[i][j])
		{
			if (map->map_arr[i][j] != '0' && map->map_arr[i][j] != '1')
			{
				if (check_letter(map, i, j) != 0)
					return (1);
				check++;
				j++;
			}
			else
				j++;
		}
		i++;
	}
	return (check);
}
