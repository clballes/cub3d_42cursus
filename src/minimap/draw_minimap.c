/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:59:46 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/29 19:10:15 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Keeps the angle between 0 and 2 * M_PI
void	angle(double *angle)
{
	if (*angle > 2 * M_PI)
		*angle = *angle - (2 * M_PI);
	if (*angle < 0)
		*angle = *angle + 2 * M_PI;
}

//Reset the map to walls and blanks so we can draw the updated player and rays.
void	clear_map( t_data *data, t_player *player)
{
	player->square->coord.color = BLACK;
	paint_square(&player->square->coord, data, player->player_size / 8);
	paint_rays(player, data, BLACK);
}

//Calculates the new position with the speed and the rotation given.
//Calculates the colision of the rays with the walls
void	update_variables(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos.x + \
		(player->advance * cos(player->rot_angle) * player->speed_adv);
	new_y = player->pos.y + \
		(player->advance * sin(player->rot_angle) * player->speed_adv);
	if (is_valid_tile_for_player(new_x, new_y, map, player))
	{
		player->pos.x = new_x;
		player->pos.y = new_y;
	}
	player->square->coord.x = (player->pos.x - player->player_size / 2) / 8;
	player->square->coord.y = (player->pos.y - player->player_size / 2) / 8;
	player->rot_angle += player->rotate * player->speed_rot;
	angle(&player->rot_angle);
	calculate_colisions(player, map);
}

//Draws the map with the updated player and rays
void	draw_minimap_and_rays(t_all *all, t_data *data, t_player *player)
{
	draw_map(data, all);
	player->square->coord.color = WHITE;
	paint_square(&player->square->coord, data, player->player_size / 8);
	paint_rays(player, data, RED);
}
