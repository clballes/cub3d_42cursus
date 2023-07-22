/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:55:44 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/22 10:56:48 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_vars *vars, t_player *player, t_all *all)
{
	// printf("advance%d\n", player->advance);
	if (keycode == KEY_ESC)
		ft_destroy_window(vars);
	printf("BBB\n");
	movements(keycode, player);
	update_map(player, &all->map, &all->data, all);
	return (0);
}

int movements(int keycode, t_player *player)
{
	printf("advance%d\n", player->advance);
	if (keycode == KEY_UP)
		player->advance = 1;
	if (keycode == KEY_DOWN)
		player->advance = -1;
	if (keycode == KEY_RIGHT)
		player->rotate = 1;
	if (keycode == KEY_LEFT)
		player->rotate = -1;
	return (0);
}

int	key_up(int keycode, t_player *player)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		player->advance = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		player->rotate = 0;
	return (0);
}