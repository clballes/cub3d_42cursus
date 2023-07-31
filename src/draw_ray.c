/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/31 15:59:03 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// void	draw_ray(t_player	*player)
// {
// 	//habra que ver cuantos rayos hay que dibujar;
// 	t_ray *ray;
// 	ray = ft_calloc(1, sizeof(t_ray));
	
// 	ray->colision_x = 0;
// 	ray->colision_y = 0;
// 	ray->down = 0;
// 	ray->left = 0;
	
// 	if (player->rotation_angle < M_PI)
// 		ray->down = 1;
// 	if (player->rotation_angle > M_PI / 2 && player->rotation_angle < 3 * M_PI / 2)
// 		ray->left = 1;
	
// }

void	horizontal_colision(t_player *player)
{
	int opposite_length;
	int step_x;
	int step_y;
	int next_hx;
	int next_hy;
	
	player->ray->colision_y = floor(player->pos_x / player->tile_size) * player->tile_size;
	if(player->ray->down)
		player->ray->colision_y += player->tile_size;
	opposite_length = player->ray->colision_y - player->pos_y;
	player->ray->colision_x = opposite_length / tan(player->rotation_angle);
	
	if(is_valid_tile(player, player->ray->colision_x, player->ray->colision_y))
	{
		//se pinta la linea hasta la colision
	}
	else
	{
		// se añade un step y se comprueba en bucle añadiendo steps
	}
	//STEP
	step_y = player->tile_size;
	step_x = step_y / tan(player->rotation_angle);
	if(player->ray->down)
		step_y = -step_y;
	if(player->ray->left)//el pone mas condiciones
		step_x = -step_x;
	// next_hx = 
	//while (is_valid_tile)
}

// void	vertical_colision(t_player *player)
// {
	
// }
int	draw_line(t_all *all, t_point start, t_point end)
{
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;

	delta.coord[X] = end.coord[X] - start.coord[X];
	delta.coord[Y] = end.coord[Y] - start.coord[Y];
	pixels = sqrt((delta.coord[X] * delta.coord[X]) + \
		(delta.coord[Y] * delta.coord[Y]));
	len = pixels;
	delta.coord[X] /= pixels;
	delta.coord[Y] /= pixels;
	pixel.coord[X] = start.coord[X];
	pixel.coord[Y] = start.coord[Y];
	while (pixels > 0)
	{
		my_mlx_pixel_put(&all->data, pixel.coord[X], pixel.coord[Y] \
			, start.color);
		pixel.coord[X] += delta.coord[X];
		pixel.coord[Y] += delta.coord[Y];
		pixels = pixels - 1;
	}
	return (1);
}

// int	draw_line(t_all *all, t_point pos_player, t_point pos_colision)
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