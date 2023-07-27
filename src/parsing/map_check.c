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

int	check_letter(t_map *map, int i, int j)
{
	if (map->map_arr[i][j] == 'S' || map->map_arr[i][j] == 'W'
		|| map->map_arr[i][j] == 'E' || map->map_arr[i][j] == 'N')
	{
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
