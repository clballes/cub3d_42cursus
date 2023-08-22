/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_colision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:06:34 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/22 12:36:14 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hcol_up(t_player *player, t_map *map, t_ray *ray)
{
	ray->colision_hor.y = ((int)(player->pos.y/map->tile_size) * map->tile_size) - 0.0001;
	ray->colision_hor.x = (ray->colision_hor.y - player->pos.y) / tan(player->ray_rot_angle) + player->pos.x;
}

void hcol_down(t_player *player, t_map *map, t_ray *ray)
{
	ray->colision_hor.y = ((int)(player->pos.y/map->tile_size) * map->tile_size) + map->tile_size;
	ray->colision_hor.x = (ray->colision_hor.y - player->pos.y) / tan(player->ray_rot_angle) + player->pos.x;
}


void	find_colision_with_horizontal_lines(t_player *player, t_map *map, t_ray *ray)
{
	if((player->ray_rot_angle > M_PI  && player->ray_rot_angle <= 2 * M_PI))
	{
		hcol_up(player, map, ray);
	}
	if((player->ray_rot_angle > 0 && player->ray_rot_angle <= M_PI))
	{
		hcol_down(player,map, ray);
	}
	while(1)
	{
		if(!is_there_a_wall(&ray->colision_hor, map, ray) && ray->colision_hor.x / map->tile_size <= map->cols && ray->colision_hor.x / map->tile_size >= 0)
		{
			if(ray->down)
			{
				ray->colision_hor.y += map->tile_size;
				ray->colision_hor.x += (map->tile_size) / tan(player->ray_rot_angle);
			}
			else
			{
				ray->colision_hor.y -= map->tile_size;
				ray->colision_hor.x += (-map->tile_size) / tan(player->ray_rot_angle);
			}
			// printf("Hx:%f, Hy%f\n",ray->colision_hor.x,ray->colision_hor.y );
		}
		else
		{
			ray->distance_horizontal = ray_length(player->pos, ray->colision_hor);
			break;
		}
	}
}