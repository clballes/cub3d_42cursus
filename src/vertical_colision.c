/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_colision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:04 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/11 11:09:19 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical_colision(t_player *player, t_map *map)
{
	float	opposite_length;
	int		step_x;
	int		step_y;
	int		colision;
	
	step_x = 0;
	step_y = 0;
	colision = 0;
	player->ray->colision_ver.x = floor(player->pos.x / map->tile_size) * map->tile_size;
	if (!player->ray->left)
		player->ray->colision_ver.x += map->tile_size;
	opposite_length = (player->ray->colision_ver.x - player->pos.x) * tan(player->rotation_angle);
	player->ray->colision_ver.y = player->pos.y + opposite_length;
	if (player->ray->left)
		player->ray->colision_ver.x--;
	if (is_there_a_wall(&player->ray->colision_ver,map))
	{
		if (player->ray->left)
			player->ray->colision_ver.x++;
		player->ray->distance_vertical = ray_length(player->pos, player->ray->colision_ver);
	}
	else
	{
		// se añade un step y se comprueba en bucle añadiendo steps
		//STEP
		step_x = map->tile_size;
		step_y = step_x * (tan(player->rotation_angle));
		if(player->ray->left)
			step_x = -step_x;
		if((!player->ray->down && step_y > 0) || (player->ray->down && step_y < 0))
			step_y = -step_y;
		while (!colision)
		{
			if(!is_there_a_wall(&player->ray->colision_ver,map))
			{
				player->ray->colision_ver.x += step_x;
				player->ray->colision_ver.y += step_y;	
			}
			else
			{
				if(player->ray->left)
					player->ray->colision_ver.x++;
				colision = 1;
				player->ray->distance_vertical = ray_length(player->pos, player->ray->colision_ver);
			}
		}
	}
}