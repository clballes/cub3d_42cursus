/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/10 12:17:06 by albagarc         ###   ########.fr       */
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


void	paint_square(t_point *point, t_data *data, int square_side)
{
	int	x;
	int	y;
	
	
	y = point->y;
	// printf("x: %d, y: %d\n", square->x, square->y);
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

void	draw_walls(t_square *wall, t_data *data, int x, int y)
{
	wall->coord.color = TURQUOISE;
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
	wall->side =  WIN_X / all->map.cols;
	wall->coord.color = TURQUOISE;
	all->map.tile_size = WIN_X /all->map.cols;
	i = 0;
	while (i < all->map.rows)
	{
		j = 0;
		while (j < all->map.cols )
		{
			if (all->map.map_arr[i][j] == '1')	
					draw_walls(wall, data, j, i);
		
			if (all->map.map_arr[i][j] == 'N' || all->map.map_arr[i][j] == 'S' || all->map.map_arr[i][j] == 'E' || all->map.map_arr[i][j] == 'W')
			{
				init_player(player, all->map.map_arr[i][j],j * all->map.tile_size, i * all->map.tile_size, all->map.tile_size);
				paint_square(&player->square->coord, data, player->square->side);
				// paint_ray(player, &all->map, data);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->data->img, 0, 0);
}


int	is_valid_tile_for_player(t_player *player, int x, int y, t_map *map)
{
	(void)player;
	t_corners	corners;
	int i;
	
	i = 0;
	// printf("tile_size: %d, x: %d, y: %d\n", map->tile_size, x, y);
	corners.up_left_x = x / map->tile_size;
	corners.up_left_y = y / map->tile_size;
	corners.up_right_x = (x - 1  + map->tile_size / 10)/ map->tile_size;
	corners.up_right_y = y / map->tile_size;
	corners.down_left_x = x / map->tile_size;
	corners.down_left_y = (y - 1 + map->tile_size / 10) / map->tile_size;
	corners.down_right_x = (x - 1 + map->tile_size / 10) / map->tile_size;
	corners.down_right_y =(y - 1 + map->tile_size / 10) / map->tile_size;
	if(map->map_arr[corners.up_left_y][corners.up_left_x]!= '1' 
		&& map->map_arr[corners.up_right_y][corners.up_right_x] != '1' 
		&& map->map_arr[corners.down_left_y][corners.down_left_x] != '1' 
		&& map->map_arr[corners.down_right_y][corners.down_right_x] != '1')
		return(1);
	return(0);
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
	int new_x;
	int new_y;

	player->square->coord.color = 0x000000;
	// player->ray->colision.color = 0x000000;
	paint_square(&player->square->coord, data, map->tile_size/10);
	// paint_ray(player, map, data);
	new_x = roundf(player->pos.x + (player->advance * cos(player->rotation_angle) * player->speed_adv));
	new_y = roundf(player->pos.y + (player->advance * sin(player->rotation_angle) * player->speed_adv));
	if(is_valid_tile_for_player(player, new_x - (map->tile_size / 20), new_y - (map->tile_size / 20), map))
	{
		player->pos.x = new_x;
		player->pos.y = new_y;
		player->square->coord.x = new_x - (map->tile_size / 20);
		player->square->coord.y = new_y - (map->tile_size / 20);
	}
	player->rotation_angle += player->rotate * player->speed_rot;
	angle(&player->rotation_angle);
	printf("rotation_angle:%f\n", player->rotation_angle);
	player->square->coord.color = 0xFFFFFF;
	// player->ray->colision.color = 0xFF0000;
	paint_square(&player->square->coord, data, map->tile_size/10);
	printf("pos.x:%f, pos.y:%f\n", player->pos.x, player->pos.y);
	
	paint_ray(player, map, data);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->data->img, 0, 0);
}

