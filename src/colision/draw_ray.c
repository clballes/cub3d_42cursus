/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/18 12:38:37 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//This function tell us the direction of the ray depending on the angle
// of the player.
void	direction_ray(t_player *player)
{
	player->ray->down = 0;
	player->ray->left = 0;
	if (player->rot_angle < M_PI)
		player->ray->down = 1;
	if (player->rot_angle > M_PI / 2 && player->rot_angle < 3 * M_PI / 2)
		player->ray->left = 1;
}

// This function returns 1 if there is a wall in the point that is receiving.
int	is_there_a_wall(t_point *point, t_map *map)
{
	t_point	matrix;
	
	matrix.x = point->x / map->tile_size;
	matrix.y = point->y / map->tile_size;
	if (matrix.x >= map->cols)
		matrix.x = map->cols - 1;
	if (matrix.x <= 0)
		matrix.x = 0;
	if (matrix.y >= map->rows)
		matrix.y = map->rows - 1;
	if (matrix.y <= 0)
		matrix.y = 0;
	if (map->map_arr[(int)matrix.y][(int)matrix.x] == '1')
		return (1);
	return (0);
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

// Compare the vertical and the horizontal colision and draw 
// the ray that is shorter.
void	paint_ray(t_player *player, t_map *map, t_data *data)
{
	direction_ray(player);
	find_colision_with_horizontal_lines(player, map);
	find_colision_with_vertical_lines(player, map);
	// vertical_colision(player, map);
	// if (player->ray->distance_horizontal < player->ray->distance_vertical)
		player->ray->colision_ver.color = 0x008000;
		player->ray->colision_hor.color = 0x800080;
		draw_line(data, player->pos, player->ray->colision_hor);
		draw_line(data, player->pos, player->ray->colision_ver);
	// else
	// 	draw_line(data, player->pos, player->ray->colision_ver);
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
	return (hypotenuse);
}
