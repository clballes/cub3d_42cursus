/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/19 16:17:58 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// #include "../mlx/mlx.h"
//malloc de esta??
int	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_X || y >= WIN_Y || x < 0 || y < 0)
		return (-1);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}


void	paint_tile(int x, int y, int tile_size, t_data *data)
{
	int	i;
	int	j;
	int	new_x;
	
	i = 0;
	j = 0;
	while (i < tile_size)
	{
		j = 0;
		new_x = x;
		while(j < tile_size)
		{
			my_mlx_pixel_put(data, new_x, y, 0x0055B4B0);
			new_x++;
			j++;
		}
		y++;
		i++;
	}
}

void	paint_player(int x, int y, int tile_size, t_data *data)
{
	int	i;
	int	j;
	int	new_x;
	int new_y;

	//new_y y new_x seran las posiciones de la estructura player;
	new_y = y + tile_size / 2 - tile_size / 20;
	i = 0;
	j = 0;
	while (i < tile_size/20 * 2)
	{
		j = 0;
		new_x = x + tile_size / 2 - tile_size / 20;
		while(j < tile_size/20 * 2)
		{
			my_mlx_pixel_put(data, new_x, new_y, 0x00ffffff);
			new_x++;
			j++;
		}
		new_y++;
		i++;
	}
}

void	draw_initial_map(t_data *data, t_player *player)
{
	int map[8][8] = {{1,1,1,1,1,1,1,1},{1,'S',0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,1,1,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1}};
	// int map[4][4] = {{1,1,1,1},{1,'S',0,1},{1,0,0,1},{1,1,1,1}};
	int x_max = 8;
	int y_max = 8;
	int i;
	int j;
	int	tile_size;

	tile_size = WIN_X / x_max;
	i = 0;
	while (i < y_max)
	{
		j = 0;
		while (j < x_max )
		{
			if (map[i][j] == 1)
			{	
				paint_tile(j * tile_size, i * tile_size, tile_size, data);
			}
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				init_player(player, map[i][j]);
				paint_player(j * tile_size, i * tile_size, tile_size, data);
			}
			j++;
		}
		i++;
	}
}