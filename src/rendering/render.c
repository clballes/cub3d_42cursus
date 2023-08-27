/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:07:39 by clballes          #+#    #+#             */
/*   Updated: 2023/07/31 19:07:41 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert RGB to hexadecimal color code

void	pixel_top_floor(int end, int start, t_all *all, int i)
{
	int j;

	j = 0;
	while(j <= end) // para el ceiling
	{
		my_mlx_pixel_put(all->data, i, j, all->element[1].color);
		j++;
	}
	while(start <= WIN_Y) // color para el floor
	{
		my_mlx_pixel_put(all->data, i, start, all->element[0].color);
		start++;
	}
}

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
		distance = all->player.ray[i].length * all->map.tile;
		alturaMuro = (WIN_Y / distance) * PlanoProyeccion;
		start = (WIN_Y / 2) - (alturaMuro / 2);
		end = start + alturaMuro;
		pixel_top_floor(end, start, all, i); //nose si cal passarli el end i el start amb -1 o no
		while(end < start)
		{
			my_mlx_pixel_put(all->data, i, end, 0xFF0000);
			end++;
		}
		i++;
	}
}