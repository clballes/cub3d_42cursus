/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/27 15:31:48 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	draw_ray(t_player	*player)
{
	//habra que ver cuantos rayos hay que dibujar;
	t_ray *ray;
	ray = ft_calloc(1, sizeof(t_ray));
	
	ray->colision_x = 0;
	ray->colision_y = 0;
	ray->down = 0;
	ray->left = 1;
	
	if (player->rotation_angle < M_PI)
		ray->down = 1;
	if (player->rotation_angle > M_PI / 2 && player->rotation_angle < 3 * M_PI / 2)
		ray->left = 1;
	
}


// int	draw_line(t_all *all, t_point start, t_point end)
// {
// 	t_point	delta;
// 	t_point	pixel;
// 	int		pixels;
// 	int		len;

// 	delta.coord[X] = end.coord[X] - start.coord[X];
// 	delta.coord[Y] = end.coord[Y] - start.coord[Y];
// 	pixels = sqrt((delta.coord[X] * delta.coord[X]) + \
// 		(delta.coord[Y] * delta.coord[Y]));
// 	len = pixels;
// 	delta.coord[X] /= pixels;
// 	delta.coord[Y] /= pixels;
// 	pixel.coord[X] = start.coord[X];
// 	pixel.coord[Y] = start.coord[Y];
// 	while (pixels > 0)
// 	{
// 		my_mlx_pixel_put(&all->data, pixel.coord[X], pixel.coord[Y] \
// 			, start.color);
// 		pixel.coord[X] += delta.coord[X];
// 		pixel.coord[Y] += delta.coord[Y];
// 		pixels = pixels - 1;
// 	}
// 	return (1);
// }