/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/22 15:58:25 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Draws a line between two points.
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

//Draw rays on the minimap.
void	paint_rays(t_player *player, t_data *data, int color)
{
	int	i;

	i = 0;
	if (player->ray[i].colision == NULL)
		return ;
	while (i < WIN_X)
	{
		player->ray[i].colision->color = color;
		draw_line(data, player->pos, *player->ray[i].colision);
		i++;
	}
}

//Transform an angle from dregrees to radians.
double	grades_to_rads(double angle)
{
	angle = angle * M_PI / 180;
	return (angle);
}

//Set the initial angle of the field of view.
void	set_angles_for_rays(t_player *player)
{
	double	initial_ray_angle;

	player->angle_increase = grades_to_rads((double)FOV / (double)WIN_X);
	initial_ray_angle = player->rot_angle - grades_to_rads((double)HALFFOV);
	angle(&initial_ray_angle);
	player->ray_angle = initial_ray_angle;
}

// Compare the vertical and the horizontal colision and draw 
// the rays that are shorter.
void	calculate_colisions(t_player *player, t_map *map)
{
	int	i;

	set_angles_for_rays(player);
	i = 0;
	while (i < WIN_X)
	{
		direction_ray(player, &player->ray[i]);
		colision_with_horizontal_lines(player, map, &player->ray[i]);
		colision_with_vertical_lines(player, map, &player->ray[i]);
		if (player->ray[i].dist_hor < player->ray[i].dist_ver)
		{
			player->ray[i].colision = &player->ray[i].col_hor;
			player->ray[i].length = player->ray[i].dist_hor;
		}
		else
		{
			player->ray[i].colision = &player->ray[i].col_ver;
			player->ray[i].length = player->ray[i].dist_ver;
		}
		player->ray[i].each_ray_angle = player->ray_angle;
		player->ray_angle += player->angle_increase;
		angle(&player->ray_angle);
		i++;
	}
}
