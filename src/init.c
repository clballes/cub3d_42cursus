/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:46:13 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/20 14:49:26 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, int orientation, int x, int y, int tile_size)
{
	
	player->first_orientation = orientation;
	if (orientation == 'N')
		player->rotation_angle = M_PI_2;
	if (orientation == 'S')
	{
		printf("entra\n");
		player->rotation_angle = 3 * M_PI_2;
	}
	if (orientation == 'E')
		player->rotation_angle = M_PI;
	if (orientation == 'W')
		player->rotation_angle = 2 * M_PI;
	player->advance = 0;
	player->rotate = 0;
	player->speed_adv = 3;
	player->speed_rot = 3 * (M_PI / 180);
	player->pos_x = x + tile_size / 2;
	player->pos_y = y + tile_size / 2;
	printf("orientation : %f\n", player->rotation_angle);
	printf("adv : %d\n", player->advance);
}
