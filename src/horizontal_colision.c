/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_colision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:06:34 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/11 11:09:35 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_colision(t_player *player, t_map *map)
{
	float adjacent_length;
	int step_x;
	int step_y;
	int colision;
	
	step_x = 0;
	step_y = 0;
	colision = 0;
	player->ray->colision_hor.y = floor(player->pos.y / map->tile_size) * map->tile_size;
	if(player->ray->down)
		player->ray->colision_hor.y += map->tile_size;
	adjacent_length = (player->pos.y - player->ray->colision_hor.y) / tan(player->rotation_angle) ;
	if(!player->ray->left && adjacent_length > 0)//
		player->ray->colision_hor.x = player->pos.x + adjacent_length;//
	else//
		player->ray->colision_hor.x = player->pos.x - adjacent_length;//
	if(!player->ray->down)
		player->ray->colision_hor.y--;
	if(is_there_a_wall(&player->ray->colision_hor,map))
	{
		if(!player->ray->down)
					player->ray->colision_hor.y++;
		player->ray->distance_horizontal = ray_length(player->pos, player->ray->colision_hor);
	}
	else
	{
		// se añade un step y se comprueba en bucle añadiendo steps
		//STEP
		step_y = map->tile_size;
		step_x = step_y / tan(player->rotation_angle);
		if(!player->ray->down)
			step_y = -step_y;
		if((player->ray->left && step_x > 0) || (!player->ray->left && step_x < 0))
			step_x = -step_x;
		while (!colision)
		{
			if((!is_there_a_wall(&player->ray->colision_hor,map)))
			{
				player->ray->colision_hor.x += step_x;
				player->ray->colision_hor.y += step_y;	
			}
			else
			{
				colision = 1;
				if(!player->ray->down)
					player->ray->colision_hor.y++;
				player->ray->distance_horizontal = ray_length(player->pos, player->ray->colision_hor);
			}
		}
	}
}