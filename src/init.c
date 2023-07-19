/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:46:13 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/19 16:17:18 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, int orientation)
{
	player = ft_calloc(1, sizeof(t_player));
	if(!player)
		return ;
	player->first_orientation = orientation;
	if (player->first_orientation == 'N')
		player->rotation_angle = M_PI_2;
	if (player->first_orientation == 'S')
		player->rotation_angle = 3 * M_PI_2;
	if (player->first_orientation == 'E')
		player->rotation_angle = M_PI;
	if (player->first_orientation == 'W')
		player->rotation_angle = 2 * M_PI;
	player->advance = 0;
	player->rotate = 0;
	player->speed_adv = 3;
	player->speed_rot = 3 * (M_PI / 180);
}
