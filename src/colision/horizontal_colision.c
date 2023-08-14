/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_colision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:06:34 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/14 11:30:42 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	first_horizontal_colision_point(t_player *player, t_map *map)
{
	double	adjacent_length;

	player->ray->colision_hor.y = floor(player->pos.y / map->tile_size) \
	* map->tile_size;
	if (player->ray->down)
		player->ray->colision_hor.y += map->tile_size;
	adjacent_length = nearbyint((player->pos.y - player->ray->colision_hor.y) \
	/ tan(player->rot_angle));
	if (!player->ray->left && adjacent_length > 0)
		player->ray->colision_hor.x = player->pos.x + adjacent_length;
	else
		player->ray->colision_hor.x = player->pos.x - adjacent_length;
	if (!player->ray->down)
		player->ray->colision_hor.y--;
}

void	next_horizontal_colision_point(t_player *player, t_map *map)
{
	int	step_x;
	int	step_y;

	step_y = map->tile_size;
	step_x = step_y / tan(player->rot_angle);
	if (!player->ray->down)
		step_y = -step_y;
	if ((player->ray->left && step_x > 0) || (!player->ray->left && step_x < 0))
		step_x = -step_x;
	while (1)
	{
		if ((!is_there_a_wall(&player->ray->colision_hor, map)))
		{
			if (player->ray->colision_hor.x < 0)
				break ;
			if (player->ray->colision_hor.x > MAP_X)
				break ;
			player->ray->colision_hor.x += step_x;
			player->ray->colision_hor.y += step_y;
		}
		else
			break ;
	}
}

void	horizontal_colision(t_player *player, t_map *map)
{
	first_horizontal_colision_point(player, map);
	if (is_there_a_wall(&player->ray->colision_hor, map))
	{
		if (!player->ray->down)
			player->ray->colision_hor.y++;
		player->ray->distance_horizontal = ray_length(player->pos, \
		player->ray->colision_hor);
	}
	else
	{
		next_horizontal_colision_point(player, map);
		if (!player->ray->down)
			player->ray->colision_hor.y++;
		player->ray->distance_horizontal = ray_length(player->pos, \
		player->ray->colision_hor);
	}
}
