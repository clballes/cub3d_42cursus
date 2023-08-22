/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:59:05 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/22 17:59:51 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_corners(double x, double y, t_map *map, t_corners *corners)
{
	corners->up_left_x = (x - PLAYER/2 ) / map->tile;
	corners->up_left_y = (y - PLAYER/2 ) / map->tile ;
	corners->down_left_x = (x - PLAYER/2) / map->tile ;
	corners->down_left_y = (y  + PLAYER/2) / map->tile ;
	corners->up_right_x = (x  + PLAYER/2) / map->tile;
	corners->up_right_y = (y - PLAYER/2 ) / map->tile;
	corners->down_right_x = (x + PLAYER/2) / map->tile ;
	corners->down_right_y = (y  + PLAYER/2) / map->tile ;
}

int	check_edges(t_map *map, t_player *player, t_corners *corners, t_point *max)
{
	if (map->map_arr[corners->up_left_y][corners->up_left_x] == '1' \
	&& map->map_arr[corners->up_right_y][corners->up_right_x] == '1') //recta horizontal del jugador superior
	{
		player->pos.y = max->y + PLAYER/2 ;
		return(1);
	}
	else if ( map->map_arr[corners->down_left_y][corners->down_left_x] == '1' \
	&& map->map_arr[corners->up_left_y][corners->up_left_x] == '1') // vertical del jugador izquierda
	{
		player->pos.x = max->x + PLAYER/2 ;
		return(1);
	}
	else if (map->map_arr[corners->down_right_y][corners->down_right_x] == '1' \
	&& map->map_arr[corners->down_left_y][corners->down_left_x] == '1') // horizontal del jugador inferior
	{
		player->pos.y = max->y + map->tile - PLAYER/2;
		return(1);
	}
	else if (map->map_arr[corners->up_right_y][corners->up_right_x] == '1' \
	&& map->map_arr[corners->down_right_y][corners->down_right_x] == '1')//vertical del jugador derecha
	{
		player->pos.x = max->x + map->tile - PLAYER/2;
		return (1);
	}
	return (0);
}

int check_only_one_corner(t_map *map, t_corners *corners)
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