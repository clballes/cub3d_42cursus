/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:55:44 by albagarc          #+#    #+#             */
/*   Updated: 2023/09/06 12:48:31 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_all *all)
{
	if (keycode == KEY_ESC)
		ft_destroy_window(all->vars);
	if (keycode == KEY_W)
		all->player.advance = 1;
	if (keycode == KEY_S)
		all->player.advance = -1;
	if (keycode == KEY_RIGHT)
		all->player.rotate = 1;
	if (keycode == KEY_LEFT)
		all->player.rotate = -1;
	if (keycode == KEY_A)
		all->player.lateral = 1;
	if (keycode == KEY_D)
		all->player.lateral = -1;
	draw_image(all);
	return (0);
}

int	key_up(int keycode, t_player *player)
{
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || \
		keycode == KEY_D)
	{
		player->lateral = 0;
		player->advance = 0;
	}
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		player->rotate = 0;
	return (0);
}
