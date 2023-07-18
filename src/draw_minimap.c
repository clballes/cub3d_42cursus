/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/18 18:17:11 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// #include "../mlx/mlx.h"

int	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_X || y >= WIN_Y || x < 0 || y < 0)
		return (-1);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}


void paint_tile(int x, int y, int height, t_data *data)
{
	int i;
	int j;
	int new_x;
	i = 0;
	j = 0;
	printf("x:%d,y:%d height:%d\n", x ,y, height);
	while (i < height)
	{
		j = 0;
		new_x = x;
		while(j < height)
		{
			// printf("x:%d,y:%d\n", x ,y);
			my_mlx_pixel_put(data, new_x, y, 0x00ff0000);
			new_x++;
			j++;
		}
		y++;
		i++;
	}
}

void	draw_initial_map(t_data *data)
{
	int map[8][8] = {{1,1,1,1,1,1,1,1},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,1,1,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1}};
	// int map[4][4] = {{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,1,1,1}};
	int x_max = 8;
	int y_max = 8;
	int i;
	int j;
	int	tile_pix_x;
	// int tile_pix_y;

	tile_pix_x = WIN_X / x_max;
	i = 0;
	// pix_x = 0;
	// pix_y = 0;
	
	printf("AAA tile_pix_x:%d\n", tile_pix_x);
	while(i < y_max)
	{
		j = 0;
		while(j < x_max )
		{
			if(map[i][j] == 1)
			{	

				paint_tile(j * tile_pix_x, i * tile_pix_x, tile_pix_x, data);
			}
			j++;
		}
		i++;
	}
	

}