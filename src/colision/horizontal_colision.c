/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_colision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:06:34 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/16 14:31:36 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculates the first  intersection point with a horizontal line
void	first_horizontal_colision_point(t_player *player, t_map *map, t_ray *ray)
{
	double	adjacent_length;

	ray->colision_hor.y = floor(player->pos.y / map->tile_size) \
	* map->tile_size;
	if (ray->down)
		ray->colision_hor.y += map->tile_size;
	adjacent_length =(player->pos.y - ray->colision_hor.y) \
	/ tan(player->ray_rot_angle);
	// printf("adj:%f\n", adjacent_length);
	// printf("tan:%f\n", tan(player->ray_rot_angle));
	// printf("rotation_angle:%f\n", player->ray_rot_angle);
	if (!ray->left && adjacent_length > 0)
	{
		ray->colision_hor.x = player->pos.x + adjacent_length;	
	}
	else
		ray->colision_hor.x = player->pos.x - adjacent_length;
	if (!ray->down)
		ray->colision_hor.y--;
}

// Calculates the next intersection points with horizontal lines and stops if 
// finds a colision with a wall.
void	next_horizontal_colision_point(t_player *player, t_map *map, t_ray *ray)
{
	int	step_x;
	int	step_y;

	step_y = map->tile_size;
	step_x = step_y / tan(player->ray_rot_angle);
	if (!ray->down)
		step_y = -step_y;
	if ((ray->left && step_x > 0) || (!ray->left && step_x < 0))
		step_x = -step_x;
	while (1)
	{
		if ((!is_there_a_wall(&ray->colision_hor, map)))
		{
			if (ray->colision_hor.x < 0)
				break ;
			if (ray->colision_hor.x > MAP_X)
				break ;
			ray->colision_hor.x += step_x;
			ray->colision_hor.y += step_y;
		}
		else
			break ;
	}
}

// calculates the distance of the ray to the horizontal colision point
void	horizontal_colision(t_player *player, t_map *map, t_ray *ray)
{
	first_horizontal_colision_point(player, map, ray);
	if (is_there_a_wall(&ray->colision_hor, map))
	{
		if (!ray->down)
		{
			printf("sumo1\n");
			ray->colision_hor.y++;
		}
		ray->distance_horizontal = ray_length(player->pos, \
		ray->colision_hor);
	}
	else
	{
		next_horizontal_colision_point(player, map, ray);
		if (!ray->down)
		{
			printf("sumo2\n");
			ray->colision_hor.y++;
		}
		ray->distance_horizontal = ray_length(player->pos, \
		ray->colision_hor);
	}
}
