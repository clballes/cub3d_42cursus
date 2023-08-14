/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_colision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:04 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/14 18:59:26 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculates the first  intersection point with a vertical line
void	first_vertical_colision_point(t_player *player, t_map *map, t_ray *ray)
{
	double	opposite_length;

	ray->colision_ver.x = floor(player->pos.x / map->tile_size) \
	* map->tile_size;
	if (!ray->left)
		ray->colision_ver.x += map->tile_size;
	opposite_length = nearbyint((ray->colision_ver.x - player->pos.x) \
	* tan(player->ray_rot_angle));
	ray->colision_ver.y = player->pos.y + opposite_length;
	if (ray->left)
		ray->colision_ver.x--;
}

// Calculates the next intersection points with vertical lines and stops if 
// finds a colision with a wall.
void	next_vertical_colision_point(t_player *player, t_map *map, t_ray *ray)
{
	int		step_x;
	int		step_y;

	step_x = map->tile_size;
	step_y = step_x * (tan(player->ray_rot_angle));
	if (ray->left)
		step_x = -step_x;
	if ((!ray->down && step_y > 0) || (ray->down && step_y < 0))
		step_y = -step_y;
	while (1)
	{
		if (!is_there_a_wall(&ray->colision_ver, map))
		{
			if (ray->colision_ver.x < 0 || ray->colision_ver.x \
			> MAP_X)
				break ;
			if (ray->colision_ver.x > MAP_X)
				break ;
			ray->colision_ver.x += step_x;
			ray->colision_ver.y += step_y;
		}
		else
			break ;
	}
}

// calculates the distance of the ray to the vertical colision point
void	vertical_colision(t_player *player, t_map *map, t_ray *ray)
{
	first_vertical_colision_point(player, map, ray);
	if (is_there_a_wall(&ray->colision_ver, map))
	{
		if (ray->left)
			ray->colision_ver.x++;
		ray->distance_vertical = ray_length(player->pos, \
		ray->colision_ver);
	}
	else
	{
		next_vertical_colision_point(player, map, ray);
		if (ray->left)
			ray->colision_ver.x++;
		ray->distance_vertical = ray_length(player->pos, \
		ray->colision_ver);
	}
}
