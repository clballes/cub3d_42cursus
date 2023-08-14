/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/14 19:36:51 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//This function tell us the direction of the ray depending on the angle
// of the player.
void	direction_ray(t_player *player, t_ray *ray)
{
	ray->down = 0;
	ray->left = 0;
	if (player->ray_rot_angle < M_PI)
		ray->down = 1;
	if (player->ray_rot_angle > M_PI / 2 && player->ray_rot_angle < 3 * M_PI / 2)
		ray->left = 1;
}

//This function returns 1 if there is a wall in the point that is receiving.
int	is_there_a_wall(t_point *point, t_map *map)
{
	t_point	matrix;

	matrix.x = point->x / map->tile_size;
	matrix.y = point->y / map->tile_size;
	// printf("X:%f, Y:%f\n",point->x, point->y);
	if (matrix.x >= map->cols)
		matrix.x = map->cols - 1;
	if (matrix.x <= 0)
		matrix.x = 0;
	if (matrix.y >= map->rows)
		matrix.y = map->rows - 1;
	if (matrix.y <= 0)
		matrix.y = 0;
	// printf("MAT_X:%d, MAT_Y:%d\n", (int)matrix.x, (int)matrix.y);
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
void	paint_ray(t_player *player, t_map *map, t_data *data, int color)
{
	int i;
	double	angle_increase;
	double initial_ray_rot_angle;

	angle_increase = grades_to_rads((double)FOV / (double)WIN_X);
	initial_ray_rot_angle = player->rot_angle - grades_to_rads((double)HALFFOV);
	angle(&initial_ray_rot_angle);
	player->ray_rot_angle = initial_ray_rot_angle;
	// printf("angle increase:%f, initial::%f\n", angle_increase, initial_ray_rot_angle);
	i = 0;
	while(i < WIN_X)
	{
		player->ray[i].colision_hor.color = color;
		player->ray[i].colision_ver.color = color;
		direction_ray(player, &player->ray[i]);
		horizontal_colision(player, map, &player->ray[i]);
		vertical_colision(player, map, &player->ray[i]);
		// printf("H_x%f, H_y%f, H_dist %f\n",player->ray[i].colision_hor.x,player->ray[i].colision_hor.y,player->ray[i].distance_horizontal);
		// printf("V_x%f, V_y%f, V_dist %f\n",player->ray[i].colision_ver.x,player->ray[i].colision_ver.y,player->ray[i].distance_vertical);
		if (player->ray[i].distance_horizontal < player->ray[i].distance_vertical)
		{
			// printf("player->ray[%d].colision_hor=%f\n", i,player->ray[i].distance_horizontal);
			draw_line(data, player->pos, player->ray[i].colision_hor);
		}
		else
			draw_line(data, player->pos, player->ray[i].colision_ver);
		player->ray_rot_angle += angle_increase;
		angle(&player->ray_rot_angle);
		i++;
	}
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
