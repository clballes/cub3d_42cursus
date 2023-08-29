/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:07:39 by clballes          #+#    #+#             */
/*   Updated: 2023/08/28 13:10:04 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//gets the texture correct return the xpm where is it stored the values from the texture
t_data	*find_texture(t_player *player, t_data *data, char c)
{
	void	*img_xpm;

	img_xpm =  NULL;
	if (player->ray->down && c == 'h') //abajo a la derecha
	{
		// printf("entro en la SO\n");
		img_xpm = data->xpm_SO;
	}
	else if(!player->ray->down && c == 'h') //arriba derecha
	{
		// printf("entro en la NO\n");
		img_xpm = data->xpm_NO;
	}
	else if(player->ray->left && c == 'v') //abajo izquierda
	{
		// printf("entro en la we\n");
		img_xpm = data->xpm_WE;
	}
	else if(!player->ray->left && c == 'v') // arriba izquierda
	{
		// printf("entro en la ea\n");
		img_xpm = data->xpm_EA;
	}
	return (img_xpm);
}

/**
 * Returns color of pixel in pos(x,y) */
int	img_pix_get(t_data *data, int x, int y)
{
	char	*pixel;

	pixel = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int *)pixel);
}

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

int	calculate_tx(int x, int y, char c)
{
	int result;

	result = 0;
	if (c == 'h')
		result = y % 64;
	else
		result = x % 64;
	return (result);
}

int	calculate_ty(int alturaMuro)
{
	int	result;
	int	y;
	int	i;

	i = 0;
	result = 64 / alturaMuro;
	y = i * result;  
	return y;
}

void	draw_render(t_all *all)
{
	int i;
	double PlanoProyeccion;
	double distance;
	double alturaMuro;
	int start;
	int end;
	t_data *data_img;
	int tx;
	int ty;

	i = 0;
	PlanoProyeccion = (WIN_X / 2) / tan(30); //sempre el mateix
	while (i < WIN_X)
	{
		data_img = find_texture(&all->player, all->data, all->player.ray[i].c);
		distance = all->player.ray[i].length * cos(all->player.rot_angle - all->player.ray[i].each_ray_angle);
		alturaMuro = (WIN_Y / distance) * PlanoProyeccion;
		tx = calculate_tx(all->player.ray[i].colision->x, all->player.ray[i].colision->y, all->player.ray[i].c);
		ty = calculate_ty(alturaMuro);
		start = (WIN_Y / 2) - (alturaMuro / 2);
		end = start + alturaMuro;
		pixel_top_floor(end, start, all, i);
			// printf("el tx es x %d\n", tx);
			// printf("el ty es x %d\n", ty);
		while(end < start)
		{
			my_mlx_pixel_put(all->data, i, end,
				img_pix_get(data_img, tx, ty)); //la funcio et retorna el int del color i poses el pixel alla, pero he de pillar el pixel de nose on
			// ty += step
			end++;
		}
		i++;
	}
}
