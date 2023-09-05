/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:07:39 by clballes          #+#    #+#             */
/*   Updated: 2023/09/05 16:35:39 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//gets the texture correct return the xpm where is it stored the values from the texture
t_data	find_texture( t_all *all, t_ray *ray)
{
	t_data	img_xpm;

	if (ray->down && ray->c == 'h') //abajo a la derecha
	{
		// printf("entro en la SO\n");
		img_xpm = all->xpm_so;
	}
	else if(!ray->down && ray->c == 'h') //arriba derecha
	{
		// printf("entro en la NO\n");
		img_xpm = all->xpm_no;
	}
	else if(ray->left && ray->c == 'v') //abajo izquierda
	{
		// printf("entro en la we\n");
		img_xpm = all->xpm_we;
	}
	else // arriba izquierda
	{
		// printf("entro en la ea\n");
		img_xpm = all->xpm_ea;
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

double	calculate_tx(double x, double y, char c)
{
	double result;

	result = 0;
	if (c == 'h')
		result = (int)x % 64;
	else
		result = (int)y % 64;
	return (result);
}

double	calculate_ty(double alturaMuro, int j)
{
	double	result;
	double	y;

	if (alturaMuro < 0)
		alturaMuro = alturaMuro * (-1);
	result = 64 / alturaMuro;
	y = j * result;  
	return (y);
}

void	draw_render(t_all *all)
{
	int i;
	double PlanoProyeccion;
	double distance;
	double alturaMuro;
	int start;
	int end;
	t_data data_img;
	double tx;
	double ty;
	int j;



	i = 0;
	PlanoProyeccion = (WIN_X / 2) / tan(30); //sempre el mateix
	while (i < WIN_X)
	{
		data_img = find_texture( all, &all->player.ray[i]);
		distance = all->player.ray[i].length * cos(all->player.rot_angle - all->player.ray[i].each_ray_angle);
		alturaMuro = (WIN_Y / distance) * PlanoProyeccion;
		tx = calculate_tx(all->player.ray[i].colision->x, all->player.ray[i].colision->y, all->player.ray[i].c);
		start = (WIN_Y / 2) - (alturaMuro / 2);
		end = start + alturaMuro;
		pixel_top_floor(end, start, all, i);
		j = 0;
		while(end < start)
		{
			ty = calculate_ty(alturaMuro, j);
			my_mlx_pixel_put(all->data, i, end,
				img_pix_get(&data_img,(int)tx, (int)ty)); //la funcio et retorna el int del color i poses el pixel alla, pero he de pillar el pixel de nose on
			// printf("el ty es %f\n", ty);
			j++;
			end++;
		}
		i++;
	}
}
