/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/17 11:37:49 by albagarc         ###   ########.fr       */
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


void	paint_square(t_point *point, t_data *data, int square_side)
{
	int	x;
	int	y;
	
	
	y = point->y;
	while (y < point->y + square_side)
	{
		x = point->x;
		while(x < point->x + square_side)
		{
			my_mlx_pixel_put(data, x, y,point->color);		
			
			x++;
		}
		y++;
	}
	
}

void	draw_walls_blanks(t_square *wall, t_data *data, int x, int y)
{
	// wall->coord.color = TURQUOISE;
	wall->coord.x = x * wall->side;
	wall->coord.y = y * wall->side;
	paint_square(&wall->coord, data, wall->side);
}

void	draw_initial_map(t_data *data, t_player *player, t_all *all)
{
	int i;
	int j;
	t_square *wall;

	
	wall = ft_calloc(1, sizeof(t_square));
	wall->side =  MAP_X / all->map.cols;
	
	all->map.tile_size = MAP_X / all->map.cols;
	i = 0;
	while (i < all->map.rows)
	{
		j = 0;
		while (j < all->map.cols )
		{
			if (all->map.map_arr[i][j] == '1')
			{
				wall->coord.color = TURQUOISE;
				draw_walls_blanks(wall, data, j, i);
			}
			else
			{
				wall->coord.color = 0x000000;
				draw_walls_blanks(wall, data, j, i);
			}
				
		
			// if (all->map.map_arr[i][j] == 'N' || all->map.map_arr[i][j] == 'S' || all->map.map_arr[i][j] == 'E' || all->map.map_arr[i][j] == 'W')
			if(i == all->map.pos_y && j == all->map.pos_x)
			{
				init_player(player, &all->map);
				paint_square(&player->square->coord, data, PLAYER);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->data->img, 0, 0);
}


int	is_valid_tile_for_player(double x, double y, t_map *map, t_player *player)
{
	(void)player;
	// t_corners	corners;
	// int i;
	int mat_x;
	int mat_y;
	// i = 0;
	// corners.up_left_x = x / map->tile_size;
	// corners.up_left_y = y / map->tile_size;
	// corners.up_right_x = (x  + map->tile_size / 10)/ map->tile_size;
	// corners.up_right_y = y / map->tile_size;
	// corners.down_left_x = x / map->tile_size;
	// corners.down_left_y = (y  + map->tile_size / 10) / map->tile_size;
	// corners.down_right_x = (x + map->tile_size / 10) / map->tile_size;
	// corners.down_right_y =(y  + map->tile_size / 10) / map->tile_size;
	// if (map->map_arr[corners.up_left_y][corners.up_left_x]!= '1' 
	// 	&& map->map_arr[corners.up_right_y][corners.up_right_x] != '1' 
	// 	&& map->map_arr[corners.down_left_y][corners.down_left_x] != '1' 
	// 	&& map->map_arr[corners.down_right_y][corners.down_right_x] != '1')
	// 	return (1);
	mat_x = x / map->tile_size;
	mat_y = y / map->tile_size;
	
	
	if(map->map_arr[(int)mat_y][(int)mat_x] != '1')
		return(1);
	// else
	// {
	// 	player->pos.x = (int)mat_x * map->tile_size;
	// 	player->pos.y = (int)mat_y * map->tile_size;
	// }
	return (0);
}


void	angle(double *angle)
{
	if (*angle > 2 * M_PI)
		*angle = *angle - (2 * M_PI);
	if (*angle < 0)
		*angle = *angle + 2 * M_PI;
	
}

void	update_map(t_player *player, t_map *map, t_data *data, t_all *all)
{
	double new_x;
	double new_y;
	player->square->coord.color = 0x000000;
	// player->ray->colision_hor.color = 0x000000;
	// player->ray->colision_ver.color = 0x000000;
	paint_square(&player->square->coord, data, PLAYER);
	// paint_ray(player, map, data);
	new_x = player->pos.x + (player->advance * cos(player->rot_angle) * player->speed_adv);
	new_y = player->pos.y + (player->advance * sin(player->rot_angle) * player->speed_adv);
	if(is_valid_tile_for_player(new_x , new_y, map, player))
	{
		
		player->pos.x = new_x;
		player->pos.y = new_y;
		player->square->coord.x = new_x - ((float)PLAYER/2);
		player->square->coord.y = new_y - ((float)PLAYER/2);
	}
	// else
	// {
	// 	// player->pos = maxima posicion sin chocar con pared 
	// }
	player->rot_angle += player->rotate * player->speed_rot;
	
	angle(&player->rot_angle);
	player->square->coord.color = 0xFFFFFF;
	player->ray->colision_hor.color = 0xFF0000;
	player->ray->colision_ver.color = 0xFF0000;
	paint_square(&player->square->coord, data, PLAYER);
	paint_ray(player, map, data);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->data->img, 0, 0);
}

