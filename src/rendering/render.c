/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:07:39 by clballes          #+#    #+#             */
/*   Updated: 2023/08/27 17:25:54 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	clear_render(t_data *data)
{
	int x;
	int y;
	x = 0;
	y = 0;
	while (y <= WIN_X)
	{
		x = 0;
		while (x <= WIN_X)
		{
			my_mlx_pixel_put(data, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	draw_render(t_all *all)
{
	int i;
	double PlanoProyeccion;
	double distance;
	double alturaMuro;
	int start;
	int end;

	i = 0;
	PlanoProyeccion = (WIN_X / 2) / tan(30); //sempre el mateix
	while (i < WIN_X)
	{
		distance = all->player.ray[i].length;
		alturaMuro = (WIN_Y / distance) * PlanoProyeccion;
		start = (WIN_Y / 2) - (alturaMuro / 2);
		end = start + alturaMuro;
		while(end < start)
		{
			my_mlx_pixel_put(all->data, i, end, 0xFF0000);
			end++;
		}
		i++;
	}
}