/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:55:44 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/26 11:27:31 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_all *all)
{

	if (keycode == KEY_ESC)
		ft_destroy_window(all->vars);
	if (keycode == KEY_UP)
		all->player.advance = 1;
		//solo avanza si puede avanzar y lo mismo en keydown
	if (keycode == KEY_DOWN)
		all->player.advance = -1;
		//solo avanza si puede avanzar y lo mismo en keydown
	if (keycode == KEY_RIGHT)
		all->player.rotate = 1;
	if (keycode == KEY_LEFT)
		all->player.rotate = -1;
	update_map(&all->player, &all->map, all->data, all);
	return (0);
}

// int movements(int keycode, t_player *player)
// {
// 	printf("advance%d\n", player->advance);
// 	if (keycode == KEY_UP)
// 		player->advance = 1;
// 	if (keycode == KEY_DOWN)
// 		player->advance = -1;
// 	if (keycode == KEY_RIGHT)
// 		player->rotate = 1;
// 	if (keycode == KEY_LEFT)
// 		player->rotate = -1;
// 	return (0);
// }

int	key_up(int keycode, t_player *player)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN)
		player->advance = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		player->rotate = 0;
	return (0);
}