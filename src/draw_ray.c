/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/11 11:10:34 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//init values for ray structure


//This function tell us the direction of the ray depending on the angle of the player.
void	direction_ray(t_player *player)
{
	player->ray->down = 0;
	player->ray->left = 0;
	if (player->rotation_angle < M_PI)
		player->ray->down = 1;
	if (player->rotation_angle > M_PI / 2 && player->rotation_angle < 3 * M_PI / 2)
		player->ray->left = 1;
}

//This function returns 1 if there is a wall in the map
int	is_there_a_wall(t_point *point, t_map *map)
{
	t_point matrix;
	// printf("POINT x: %f, y: %f\n", point->x, point->y);
	if(point->x >= WIN_X)
		point->x = WIN_X - 1;
	if(point->x <= 0)
		point->x = 0;
	if(point->y >= WIN_Y)
		point->y = WIN_Y - 1;
	if (point->y <= 0)
		point->y = 0;
	matrix.x = point->x / map->tile_size;
	matrix.y = point->y / map->tile_size;
	// printf("MATRIX x: %f, y: %f\n", matrix.x, matrix.y);
	// printf("MATRIX INT: %d, y: %d\n", (int)matrix.x, (int)matrix.y);
	if(map->map_arr[(int)matrix.y][(int)matrix.x] == '1')
		return(1);
	return(0);
}

int	draw_line(t_data *data, t_point pos_player, t_point pos_colision)
{
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;
	
	delta.x = pos_colision.x - pos_player.x;
	delta.y = pos_colision.y - pos_player.y;
	pixels = sqrt((delta.x * delta.x) + \
		(delta.y * delta.y));
	len = pixels;
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = pos_player.x;
	pixel.y = pos_player.y;
	while (pixels > 0)
	{
		my_mlx_pixel_put(data, pixel.x, pixel.y \
			, pos_colision.color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels = pixels - 1;
	}
	return (1);
}

void	paint_ray(t_player *player, t_map *map, t_data *data)
{
	direction_ray(player);
	horizontal_colision(player, map);
	vertical_colision(player, map);
	if(player->ray->distance_horizontal < player->ray->distance_vertical)
		draw_line(data, player->pos, player->ray->colision_hor);
	else
		draw_line(data, player->pos, player->ray->colision_ver);
		
}

//Pitagoras to know the length of the ray
float	ray_length(t_point pos, t_point col)
{
	float	hypotenuse;
	float	x;
	float	y;

	if (pos.x > col.x)
		x = pos.x - col.x;
	else
		x = col.x - pos.x;
	if (pos.y > col.y)
		y = pos.y - col.y;
	else
		y = col.y - pos.y;
	hypotenuse = sqrt((x * x) + (y * y));
	return(hypotenuse);
}