/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/22 18:02:38 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	double	x;
	double	y;
	
	
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
	wall->coord.x = x * wall->side;
	wall->coord.y = y * wall->side;
	paint_square(&wall->coord, data, wall->side);
}

void	draw_map(t_data *data, t_all *all)
{
	int i;
	int j;
	t_square *wall;

	wall = ft_calloc(1, sizeof(t_square));
	wall->side =  MAP_X / all->map.cols;
	i = -1;
	while (++i < all->map.rows)
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
				wall->coord.color = BLACK;
				draw_walls_blanks(wall, data, j, i);
			}
			j++;
		}
	}
}

void	angle(double *angle)
{
	if (*angle > 2 * M_PI)
		*angle = *angle - (2 * M_PI);
	if (*angle < 0)
		*angle = *angle + 2 * M_PI;
	
}

void	update_variables(t_player *player, t_map *map)
{
	double new_x;
	double new_y;

	new_x = player->pos.x + (player->advance * cos(player->rot_angle) * player->speed_adv);
	new_y = player->pos.y + (player->advance * sin(player->rot_angle) * player->speed_adv);
	if(is_valid_tile_for_player(new_x , new_y, map, player))
	{
		player->pos.x = new_x;
		player->pos.y = new_y;
	}
	player->square->coord.x = player->pos.x - ((float)PLAYER/2);
	player->square->coord.y = player->pos.y - ((float)PLAYER/2);
	player->rot_angle += player->rotate * player->speed_rot;
	angle(&player->rot_angle);
	calculate_colisions(player, map);
}

void	clear_map( t_data *data, t_player *player)
{
	player->square->coord.color = BLACK;//clear map
	paint_square(&player->square->coord, data, PLAYER);//clear map
	paint_rays(player, data, BLACK);//clear map
}

void draw_minimap_and_rays(t_all *all, t_data *data, t_player *player)
{
	draw_map(data, all);
	player->square->coord.color = WHITE;
	paint_square(&player->square->coord, data, PLAYER);
	paint_rays(player, data, RED);
}


