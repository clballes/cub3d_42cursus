/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:59:05 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/27 19:14:26 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Locate the position of the corners of the square that represents the player.
void	set_player_corners(double x, double y, t_map *map, t_corners *corners)
{
	double	player_size;

	player_size = map->tile / 5;
	corners->up_left_x = (x - player_size / 2) / map->tile;
	corners->up_left_y = (y - player_size / 2) / map->tile;
	corners->down_left_x = (x - player_size / 2) / map->tile;
	corners->down_left_y = (y + player_size / 2) / map->tile;
	corners->up_right_x = (x + player_size / 2) / map->tile;
	corners->up_right_y = (y - player_size / 2) / map->tile;
	corners->down_right_x = (x + player_size / 2) / map->tile;
	corners->down_right_y = (y + player_size / 2) / map->tile;
}

//check if the edges of the square are going to be
//  inside a wall and in that 
//case readjust the position of the player. 
//first if : horizontal up   // second if: vertical left
//third if : horizontal down // fourth if: vertical right.
int	check_edges(t_map *map, t_player *player, t_corners *corners, t_point *max)
{
	if (map->map_arr[corners->up_left_y][corners->up_left_x] == '1' \
	&& map->map_arr[corners->up_right_y][corners->up_right_x] == '1')
	{
		player->pos.y = max->y + player->player_size / 2 ;
		return (1);
	}
	else if (map->map_arr[corners->down_left_y][corners->down_left_x] == '1' \
	&& map->map_arr[corners->up_left_y][corners->up_left_x] == '1')
	{
		player->pos.x = max->x + player->player_size / 2 ;
		return (1);
	}
	else if (map->map_arr[corners->down_right_y][corners->down_right_x] == '1' \
	&& map->map_arr[corners->down_left_y][corners->down_left_x] == '1')
	{
		player->pos.y = max->y + map->tile - player->player_size / 2;
		return (1);
	}
	else if (map->map_arr[corners->up_right_y][corners->up_right_x] == '1' \
	&& map->map_arr[corners->down_right_y][corners->down_right_x] == '1')
	{
		player->pos.x = max->x + map->tile - player->player_size / 2;
		return (1);
	}
	return (0);
}

//Check if 1 corner is inside a wall in that case it doesn't move 
int	check_only_one_corner(t_map *map, t_corners *corners)
{
	if (map->map_arr[corners->up_left_y][corners->up_left_x] == '1')
		return (1);
	else if (map->map_arr[corners->up_right_y][corners->up_right_x] == '1')
		return (1);
	else if (map->map_arr[corners->down_left_y][corners->down_left_x] == '1')
		return (1);
	else if (map->map_arr[corners->down_right_y][corners->down_right_x] == '1')
		return (1);
	return (0);
}

//Check if the new position of the player is valid, 
//If it is valid the player will advance.
int	is_valid_tile_for_player(double x, double y, t_map *map, t_player *player)
{
	t_corners	corners;
	int			mat_x;
	int			mat_y;
	t_point		max;

	set_player_corners(x, y, map, &corners);
	max.x = (int)(player->pos.x / map->tile) * map->tile;
	max.y = (int)(player->pos.y / map->tile) * map->tile;
	if (check_edges(map, player, &corners, &max))
		return (0);
	else if (check_only_one_corner(map, &corners))
		return (0);
	mat_x = x / map->tile;
	mat_y = y / map->tile;
	if (map->map_arr[(int)mat_y][(int)mat_x] != '1')
		return (1);
	return (0);
}
