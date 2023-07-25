/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:44 by albagarc         ###   ########.fr       */
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
	// printf("1:%p\n", dst);
	*(unsigned int *)dst = color;
	// printf("2:%p\n", dst);
	return (0);
}


void	paint_square(t_square *square, t_data *data)
{
	int	x;
	int	y;
	
	
	y = square->y;
	printf("x: %d, y: %d\n", square->x, square->y);
	while (y < square->y + square->side)
	{
		x = square->x;
		while(x < square->x + square->side)
		{
			my_mlx_pixel_put(data, x, y,square->color);		
			
			x++;
		}
		y++;
	}
	
}
// 0xc1272d
// void	paint_init_player(int x, int y, int tile_size, t_data *data)
// {
// 	int	i;
// 	int	j;
// 	int	new_x;
// 	int new_y;

// 	//new_y y new_x seran las posiciones de la estructura player;
// 	new_y = y + tile_size / 2 - tile_size / 20;
// 	i = 0;
// 	j = 0;
// 	while (i < tile_size/20 * 2)
// 	{
// 		j = 0;
// 		new_x = x + tile_size / 2 - tile_size / 20;
// 		while(j < tile_size/20 * 2)
// 		{
// 			my_mlx_pixel_put(data, new_x, new_y, 0x00ffffff);
// 			new_x++;
// 			j++;
// 		}
// 		new_y++;
// 		i++;
// 	}
// }
// void	update_player(int x, int y, int tile_size, t_all *all)
// {
// 	printf("la x es %d, la y es %d, la tile soze es %d, la data es p %p\n", x, y, tile_size, all->data);
// 	int	i;
// 	int	j;
	
// 	i = 0;
	
// 	while (i < tile_size/10 )
// 	{
// 		j = 0;
// 		while(j < tile_size/10 )
// 		{
// 			printf("entras? x = %d y = %d\n", x, y);
// 			my_mlx_pixel_put(all->data, x, y, 0xc1272d);
		
// 			x++;
// 			j++;
// 		}
// 		y++;
// 		i++;
// 	}
	
// }
void	draw_walls(t_square *wall, t_data *data, int x, int y)
{
	wall->color = TURQUOISE;
	wall->x = x * wall->side;
	wall->y = y * wall->side;
	paint_square(wall, data);
}

void	draw_initial_map(t_data *data, t_player *player, t_all *all)
{
	(void)player;
	int map[8][8] = {{1,1,1,1,1,1,1,1},{1,'N',0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,1,1,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1}};
	int x_max = 8;
	int y_max = 8;
	int i;
	int j;
	t_square *wall;
	
	wall = ft_calloc(1, sizeof(t_square));
	wall->side =  WIN_X / x_max;
	wall->color = TURQUOISE;
	all->map.tile_size = WIN_X / x_max;
	// player_position = all->map.tile_size / 2 - all->map.tile_size / 20;
	i = 0;
	while (i < y_max)
	{
		j = 0;
		while (j < x_max )
		{
			if (map[i][j] == 1)	
					draw_walls(wall, data, j, i);
		
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{

				init_player(player, map[i][j],j * all->map.tile_size, i * all->map.tile_size, all->map.tile_size);
				paint_square(player->square, data);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->data->img, 0, 0);
}

void	update_map(t_player *player, t_map *map, t_data *data, t_all *all)
{
	int new_x;
	int new_y;
	(void)data;
	(void)map;
	player->square->color = 0x000000;
	paint_square(player->square, data);
	new_x = player->square->x + (player->advance * cos(player->rotation_angle) * player->speed_adv);
	new_y = player->square->y + (player->advance * sin(player->rotation_angle) * player->speed_adv);
	// printf("new_x: %d, new_y: %d rotation_angle: %f\n", new_x, new_y, player->rotation_angle);
	player->square->x = new_x;
	player->square->y = new_y;
	player->square->color = 0xFFFFFF;
	paint_square(player->square, data);
	// paint_square(player->pos_x, player->pos_y, map->tile_size/10, data, 0xc1272d);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->data->img, 0, 0);
}