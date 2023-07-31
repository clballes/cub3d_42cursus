/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:46:13 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/31 16:08:48 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, int orientation, int x, int y, int tile_size)
{
	t_square *square;
	
	square = ft_calloc(1, sizeof(t_square));
	player->square = square;
	player->tile_size = tile_size;
	player->first_orientation = orientation;
	if (orientation == 'N')
		player->rotation_angle = 3 * M_PI_2;
	if (orientation == 'S')
		player->rotation_angle =  M_PI_2;
	if (orientation == 'E')
		player->rotation_angle = 2 * M_PI;
	if (orientation == 'W')
		player->rotation_angle =  M_PI;
	player->advance = 0;
	player->rotate = 0;
	player->speed_adv = 1;
	player->speed_rot = 3 * (M_PI / 180);
	printf("al inicio speed_rot = %f\n", player->speed_rot);
	player->pos->x = x + tile_size / 2; //centro del cuadrado que pintamos_x
	player->pos->y = y + tile_size / 2; //centro del cuadrado que pintamos_y
	player->square->side = tile_size/10;
	player->square->x = x + tile_size / 2 - (tile_size / 20);
	player->square->y = y + tile_size / 2 - (tile_size / 20);
	printf("init_x:%d, init_y:%d\n", player->square->x, player->square->y );
	player->square->color = 0xFFFFFF;
}
