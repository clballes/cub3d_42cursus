/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/03 16:39:44 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int	draw_line(t_data *all, t_point pos_player, t_point pos_colision);
//init values for ray structure
void	init_ray(t_player	*player)
{
	//habra que ver cuantos rayos hay que dibujar;
	t_ray *ray;
	ray = ft_calloc(1, sizeof(t_ray));
	player->ray = ray;
	player->ray->colision.x = 0;
	player->ray->colision.y = 0;
	player->ray->down = 0;
	player->ray->left = 0;
}

//This function tell us the direction of the ray depending on the angle of the player.
void	direction_ray(t_player *player)
{
	if (player->rotation_angle < M_PI)
		player->ray->down = 1;
	if (player->rotation_angle > M_PI / 2 && player->rotation_angle < 3 * M_PI / 2)
		player->ray->left = 1;
}

//This function returns 1 if there is a wall in the map
int	is_there_a_wall(t_point *point, t_map *map)
{
	t_point colision;
	printf("POINT x: %d, y: %d\n", point->x, point->y);
	colision.x = point->x / map->tile_size;
	colision.y = point->y / map->tile_size;
	// if(point->y % map->tile_size ==0 )
	// 	colision.y -= 1;
	printf("MATRIZ x: %d, y: %d\n", colision.x, colision.y);
	if(map->map_arr[colision.y][colision.x]== '1')
		return(1);
	return(0);
}


void	horizontal_colision(t_player *player, t_map *map, t_data *data)
{
	float opposite_length;
	int step_x;
	int step_y;
	int colision;
	
	step_x = 0;
	step_y = 0;
	colision = 0;
	player->ray->colision.y = floor(player->pos.x/ map->tile_size) * map->tile_size;
	if(player->ray->down)
		player->ray->colision.y += map->tile_size;
	opposite_length = player->pos.y - player->ray->colision.y;
	printf("ANTESque hay aqui ray->pos.x:%d\n",player->pos.x);
	printf("opposite_length:%f\n", opposite_length);
	printf("tangente:%f\n", tan(player->rotation_angle));
	// if((tan(player->rotation_angle)!= 0)
	player->ray->colision.x = player->pos.x + (opposite_length / (tan(player->rotation_angle)));
	printf("DESPUESque hay aqui ray->pos.x:%d\n",player->pos.x);
	if(!player->ray->down)
		player->ray->colision.y--;
	if(is_there_a_wall(&player->ray->colision,map))
		draw_line(data, player->pos, player->ray->colision);//se pinta la linea hasta la colision
	else
	{
		// se añade un step y se comprueba en bucle añadiendo steps
		//STEP
		step_y = map->tile_size;
		step_x = step_y / tan(player->rotation_angle);
		if(!player->ray->down)
			step_y = -step_y;
		if((player->ray->left && step_x > 0) || (!player->ray->left && step_x < 0))
			step_x = -step_x;
		while (!colision)
		{
			if(!is_there_a_wall(&player->ray->colision,map))
			{
				player->ray->colision.x += step_x;
				player->ray->colision.y += step_y;	
			}
			else
			{
				colision = 1;
				draw_line(data, player->pos, player->ray->colision);
			}
		}
	}
}
// void	vertical_colision(t_player *player, t_map *map, t_data *data)
// {
// 	float opposite_length;
// 	int step_x;
// 	int step_y;
// 	int colision;
	
// 	step_x = 0;
// 	step_y = 0;
// 	colision = 0;
// 	player->ray->colision.x = floor(player->pos.y/ map->tile_size) * map->tile_size;
// 	if(player->ray->down)
// 		player->ray->colision.x += map->tile_size;
// 	opposite_length = player->pos.x - player->ray->colision.x;
// 	player->ray->colision.y = player->pos.y + opposite_length / (tan(player->rotation_angle));
// 	if(!player->ray->down)
// 		player->ray->colision.x--;
// 	if(is_there_a_wall(&player->ray->colision,map))
// 		draw_line(data, player->pos, player->ray->colision);//se pinta la linea hasta la colision
// 	else
// 	{
// 		// se añade un step y se comprueba en bucle añadiendo steps
// 		//STEP
// 		step_x= map->tile_size;
// 		step_y = step_x / tan(player->rotation_angle);
// 		if(!player->ray->down)
// 			step_x = -step_x;
// 		if((player->ray->left && step_y > 0) || (!player->ray->left && step_y < 0))
// 			step_y = -step_y;
// 		while (!colision)
// 		{
// 			if(!is_there_a_wall(&player->ray->colision,map))
// 			{
// 				player->ray->colision.x += step_x;
// 				player->ray->colision.y += step_y;	
// 			}
// 			else
// 			{
// 				colision = 1;
// 				draw_line(data, player->pos, player->ray->colision);
// 			}
// 		}
// 	}
	
// }

int	draw_line(t_data *data, t_point pos_player, t_point pos_colision)
{
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;
	
	pos_player.color = 0xFF0000;
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
		my_mlx_pixel_put(data, pixel.x, pixel.y \
			, pos_player.color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels = pixels - 1;
	}
	return (1);
}


void	paint_ray(t_player *player, t_map *map, t_data *data)
{
	
	init_ray(player);
	direction_ray(player);
	horizontal_colision(player, map, data);
	// vertical_colision(player, map, data);
	
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