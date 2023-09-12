/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:59:52 by clballes          #+#    #+#             */
/*   Updated: 2023/07/31 13:25:44 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_digit(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			check++;
		else if (!ft_is_space(str[i]))
		{
			write(2, "error: wrong syntax for RGB colors\n", 36);
			return (1);
		}
		i++;
	}
	if (check == 0)
	{
		write(2, "error: check we have 3 numbers for RGB\n", 39);
		return (1);
	}
	return (0);
}

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
	map->copy_map = ft_calloc(map->rows, sizeof(char *));
	if (map->copy_map == NULL)
		return ;
	while (i < map->rows)
	{
		map->copy_map[i] = ft_strdup(map->map_arr[i]);
		i++;
	}
}

void	max_cols(t_map *map)
{
	int	i;
	int	j;

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
