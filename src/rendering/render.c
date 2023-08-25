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


// void	print_pixels(t_ray *ray_px)
// {

// }
void	draw_render(t_all *all)
{
	// int i = 0;
	double PlanoProyeccion;
	double distance;
	double alturaMuro;

	PlanoProyeccion = (WIN_X / 2) / tan(30);
	distance = all->player.ray[WIN_X / 2].length;
	alturaMuro = WIN_Y / distance * PlanoProyeccion;
	printf("plano proyeccion es: %f\n", PlanoProyeccion);
	printf("la distance es %f\n", distance);
	printf("altura muro es  %f\n", alturaMuro);

	// -------------------- PART 2
	int start = (WIN_Y / 2) - (alturaMuro / 2);
	int end = start + alturaMuro;
	printf("la y es %d\n", start);
	printf("la y es %d\n", end);

	//PART 3 ---- priniting pixels while
	// while(i < WIN_X)
	// {
	// 	print_pixels(all->player.ray[i]);
	// 	i++;
	// }
	// print_pixels();
	// la x es la columna q cada rayo lleva asignada

	// printf("el rayo length %f\n", all->player.ray[WIN_X / 2].length);
	// printf("el rayo length %d\n", all->map.tile);
	// printf("tay anngleee %f\n", player->ray[WIN_X / 2].each_ray_angle);
}