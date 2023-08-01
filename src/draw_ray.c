/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/01 17:42:17 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

//init values for ray structure
void	init_ray(t_player	*player)
{
	//habra que ver cuantos rayos hay que dibujar;
	t_ray *ray;
	ray = ft_calloc(1, sizeof(t_ray));
	player->ray = ray;
	ray->colision_x = 0;
	ray->colision_y = 0;
	ray->intersection_x = 0;
	ray->intersection_y = 0;
	ray->down = 0;
	ray->left = 0;
	
	
}

//This function tell us the direction of the ray depending on the angle of the player.
void	direction_ray(t_player *player)
{
	if (player->rotation_angle < M_PI)
		player->ray->down = 1;
	if (player->rotation_angle > M_PI / 2 && player->rotation_angle < 3 * M_PI / 2)
		player->ray->left = 1;
	// printf("player is looking down?:%d\n",player->ray->down);
}

void	horizontal_colision(t_player *player, t_map *map)
{
	int opposite_length;
	int step_x;
	int step_y;
	int next_hx;
	int next_hy;
	int colision;
	
	step_x = 0;
	step_y = 0;
	colision = 0;
	player->ray->intersection_y = floor(player->pos.x/ player->tile_size) * player->tile_size;
	if(player->ray->down)
		player->ray->intersection_y += player->tile_size;
	opposite_length = player->ray->intersection_y - player->pos.y;
	player->ray->intersection_x = opposite_length / tan(player->rotation_angle);
	
	if(is_valid_tile(player, player->ray->intersection_x, player->ray->intersection_y, map))
	{
		//se pinta la linea hasta la colision
	}
	else
	{
		// se añade un step y se comprueba en bucle añadiendo steps
	}
	//STEP
	step_y = map->tile_size;
	step_x = step_y / tan(player->rotation_angle);
	if(!player->ray->down)
		step_y = -step_y;
	if(player->ray->left && step_x > 0 || !player->ray->left && step_x < 0)
		step_x = -step_x;
	next_hx = player->ray->intersection_x;
	next_hy = player->ray->intersection_y; 
	if(!player->ray->down)
		next_hy--;
	while (!colision)
	{
		if(is_valid_tile(player, next_hx, next_hy, map))
		{
			next_hx += step_x;
			next_hy += step_y;	
		}
		else
		{
			colision = 1;
			player->ray->colision_x = next_hx;
			player->ray->colision_y = next_hy;
			
		}
		// next_h= 
	}
}

// // // void	vertical_colision(t_player *player)
// // // {
	
// // // }

int	draw_line(t_all *all, t_point pos_player, t_point pos_colision)
{
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;

	delta.x = pos_colision.x - pos_player.x;
	delta.y = pos_colision.y - pos_player.y;
	pixels = sqrt((delta.x * delta.x) + \
		(delta.y * delta.y));
	len = pixels;
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = pos_player.x;
	pixel.y = pos_player.y;
	while (pixels > 0)
	{
		my_mlx_pixel_put(&all->data, pixel.x, pixel.y \
			, pos_player.color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels = pixels - 1;
	}
	return (1);
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