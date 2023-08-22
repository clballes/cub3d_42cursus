/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_colision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:06:34 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/22 15:39:22 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Calculates the first intersection point with a horizontal line
//if we are looking UP.
void	hcol_up(t_player *player, t_map *map, t_ray *ray)
{
	ray->col_hor.y = ((int)(player->pos.y / map->tile) * map->tile) - 0.0001;
	ray->col_hor.x = (ray->col_hor.y - player->pos.y) / \
	tan(player->ray_angle) + player->pos.x;
}

//Calculates the first intersection point with a horizontal line
//if we are looking DOWN.
void	hcol_down(t_player *player, t_map *map, t_ray *ray)
{
	ray->col_hor.y = ((int)(player->pos.y / map->tile) * map->tile) + map->tile;
	ray->col_hor.x = (ray->col_hor.y - player->pos.y) / \
	tan(player->ray_angle) + player->pos.x;
}

//Adds to the intersection point a step to check the next horizontal
//The step is different if we are looking up or down.
void	add_step_to_next_horizontal(t_player *player, t_map *map, t_ray *ray)
{
	if (ray->down)
	{
		ray->col_hor.y += map->tile;
		ray->col_hor.x += map->tile / tan(player->ray_angle);
	}
	else
	{
		ray->col_hor.y -= map->tile;
		ray->col_hor.x += (-map->tile) / tan(player->ray_angle);
	}
}

//Finds the colision point with horizontal lines and saves the distance.
void	colision_with_horizontal_lines(t_player *player, t_map *map, t_ray *ray)
{
	if ((player->ray_angle > M_PI && player->ray_angle <= 2 * M_PI))
		hcol_up(player, map, ray);
	if ((player->ray_angle > 0 && player->ray_angle <= M_PI))
		hcol_down(player, map, ray);
	while (1)
	{
		if (!is_there_a_wall(&ray->col_hor, map, ray) \
			&& ray->col_hor.x / map->tile <= map->cols \
			&& ray->col_hor.x / map->tile >= 0)
			add_step_to_next_horizontal(player, map, ray);
		else
		{
			ray->dist_hor = ray_length(player->pos, ray->col_hor);
			break ;
		}
	}
}
