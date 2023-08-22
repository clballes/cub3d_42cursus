/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_colision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:04 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/22 15:38:45 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Calculates the first intersection point with a vertical line
//if we are looking LEFT.
void	vcol_left(t_player *player, t_map *map, t_ray *ray)
{
	ray->col_ver.x = ((int)(player->pos.x / map->tile) * map->tile) - 0.0001;
	ray->col_ver.y = (ray->col_ver.x - player->pos.x) * \
	tan(player->ray_angle) + player->pos.y;
}

//Calculates the first intersection point with a vertical line
//if we are looking RIGHT.
void	vcol_right(t_player *player, t_map *map, t_ray *ray)
{
	ray->col_ver.x = ((int)(player->pos.x / map->tile) * map->tile) + map->tile;
	ray->col_ver.y = ((ray->col_ver.x - player->pos.x) * \
	tan(player->ray_angle)) + player->pos.y;
}

//Adds to the intersection point a step to check the next vertical
//The step is different if we are looking left or right.
void	add_step_to_next_vertical(t_player *player, t_map *map, t_ray *ray)
{
	if (!ray->left)
	{
		ray->col_ver.x += map->tile;
		ray->col_ver.y += map->tile * tan(player->ray_angle);
	}
	else
	{
		ray->col_ver.x -= map->tile;
		ray->col_ver.y += (-map->tile) * tan(player->ray_angle);
	}
}

//Finds the colision point with vertical lines and saves the distance.
void	colision_with_vertical_lines(t_player *player, t_map *map, t_ray *ray)
{
	if (player->ray_angle > (M_PI / 2) && player->ray_angle < (3 * M_PI / 2))
		vcol_left(player, map, ray);
	if ((player->ray_angle > (3 * M_PI / 2) || player->ray_angle < (M_PI / 2)))
		vcol_right(player, map, ray);
	while (1)
	{
		if (!is_there_a_wall(&ray->col_ver, map, ray) \
			&& ray->col_ver.y / map->tile <= map->rows \
			&& ray->col_ver.y / map->tile >= 0)
			add_step_to_next_vertical(player, map, ray);
		else
		{
			ray->dist_ver = ray_length(player->pos, ray->col_ver);
			break ;
		}
	}
}
