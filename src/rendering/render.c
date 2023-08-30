/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:07:39 by clballes          #+#    #+#             */
/*   Updated: 2023/08/29 17:51:09 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/** Returns color of pixel in pos(x,y) */
int	img_pix_get(t_data *data, int x, int y)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	return (*(int *)pixel);
}

// Function to convert RGB to hexadecimal color code
void	pixel_top_floor(int end, int start, t_all *all, int i)
{
	int	j;

	j = 0;
	while (j <= end)
	{
		my_mlx_pixel_put(all->data, i, j, all->element[1].color);
		j++;
	}
	while (start <= WIN_Y)
	{
		my_mlx_pixel_put(all->data, i, start, all->element[0].color);
		start++;
	}
}

void	clear_render(t_data *data)
{
	int	x;
	int	y;

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

void	calculations(t_all *all, t_render *rd, int i)
{
	rd->distance = all->player.ray[i].length
		* cos(all->player.rot_angle - all->player.ray[i].each_ray_angle);
	rd->altura_muro = (WIN_Y / rd->distance) * rd->plano_proyeccion;
	rd->tx = calculate_tx(all->player.ray[i].colision->x,
			all->player.ray[i].colision->y, all->player.ray[i].c);
	rd->start = (WIN_Y / 2) - (rd->altura_muro / 2);
	rd->end = rd->start + rd->altura_muro;
	pixel_top_floor(rd->end, rd->start, all, i);
}

void	draw_render(t_all *all)
{
	t_render	rd;
	t_data		data_img;
	int			i;
	int			j;

	rd = all->render;
	i = 0;
	rd.plano_proyeccion = (WIN_X / 2) / tan(30);
	while (i < WIN_X)
	{
		data_img = find_texture(all, &all->player.ray[i]);
		calculations(all, &rd, i);
		j = 0;
		while (rd.end < rd.start)
		{
			rd.ty = calculate_ty(rd.altura_muro, j);
			my_mlx_pixel_put(all->data, i, rd.end,
				img_pix_get(&data_img, (int)rd.tx, (int)rd.ty));
			j++;
			rd.end++;
		}
		i++;
	}
}
