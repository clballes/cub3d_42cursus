/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_colision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:06:34 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/18 12:26:42 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hcol_up(t_player *player, t_map *map)
{
	player->ray->colision_hor.y = ((int)(player->pos.y/map->tile_size) * map->tile_size) - 0.0001;
	player->ray->colision_hor.x = (player->ray->colision_hor.y - player->pos.y) / tan(player->rot_angle) + player->pos.x;
}

void hcol_down(t_player *player, t_map *map)
{
	player->ray->colision_hor.y = ((int)(player->pos.y/map->tile_size) * map->tile_size) + map->tile_size;
	player->ray->colision_hor.x = (player->ray->colision_hor.y - player->pos.y) / tan(player->rot_angle) + player->pos.x;
}


void	find_colision_with_horizontal_lines(t_player *player, t_map *map)
{
	if((player->rot_angle > M_PI  && player->rot_angle <= 2 * M_PI))
	{
		hcol_up(player, map);
	}
	if((player->rot_angle > 0 && player->rot_angle <= M_PI))
	{
		printf("DOWN\n");
		hcol_down(player,map);
	}
	while(1)
	{
		if(!is_there_a_wall(&player->ray->colision_hor, map)&& player->ray->colision_hor.x / map->tile_size <= map->cols)
			{
				if(player->ray->down)
				{
					player->ray->colision_hor.y += map->tile_size;
					player->ray->colision_hor.x += (map->tile_size) / tan(player->rot_angle);
				}
				else
				{
					player->ray->colision_hor.y -= map->tile_size;
					player->ray->colision_hor.x += (-map->tile_size) / tan(player->rot_angle);
				}
			}
		else
		{
			break;
		}
		
	}
}