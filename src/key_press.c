/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:55:44 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/19 16:28:40 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_vars *vars, t_player *player)
{
	if (keycode == KEY_ESC)
		ft_destroy_window(vars);
	movements(keycode, player);

	return (0);
}

int movements(int keycode, t_player *player)
{
	if (keycode == KEY_UP)
		player->advance = 1;
	if (keycode == KEY_DOWN)
		player->advance = -1;
	if (keycode == KEY_RIGHT)
		player->rotate = 1;
	if (keycode == KEY_LEFT)
		player->rotate = -1;
}

int	key_up(int keycode, t_player *player)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		player->advance = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		player->rotate = 0;
	return (0);
}