/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/10 14:39:00 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	vertical_colision(t_player *player, t_map *map/*, t_data *data*/);
float	ray_length(t_point pos, t_point col);

int	draw_line(t_data *all, t_point pos_player, t_point pos_colision);
//init values for ray structure
void	init_ray(t_player	*player)
{
	//habra que ver cuantos rayos hay que dibujar;
	t_ray *ray;
	ray = ft_calloc(1, sizeof(t_ray));
	player->ray = ray;
	player->ray->colision_hor.x = 0;
	player->ray->colision_hor.y = 0;
	player->ray->colision_ver.x = 0;
	player->ray->colision_ver.y = 0;
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
	t_point matrix;
	printf("POINT x: %f, y: %f\n", point->x, point->y);
	if(point->x >= WIN_X)
		point->x = WIN_X - 1;
	if(point->x <= 0)
		point->x = 0;
	if(point->y >= WIN_Y)
		point->y = WIN_Y - 1;
	if (point->y <= 0)
		point->y = 0;
	matrix.x = point->x / map->tile_size;
	matrix.y = point->y / map->tile_size;
	printf("MATRIX x: %f, y: %f\n", matrix.x, matrix.y);
	printf("MATRIX INT: %d, y: %d\n", (int)matrix.x, (int)matrix.y);
	if(map->map_arr[(int)matrix.y][(int)matrix.x] == '1')
		return(1);
	return(0);
}

void	horizontal_colision(t_player *player, t_map *map/*, t_data *data*/)
{
	float adjacent_length;
	int step_x;
	int step_y;
	int colision;
	
	step_x = 0;
	step_y = 0;
	colision = 0;
	player->ray->colision_hor.y = floor(player->pos.y / map->tile_size) * map->tile_size;
	if(player->ray->down)
		player->ray->colision_hor.y += map->tile_size;
	adjacent_length = (player->pos.y - player->ray->colision_hor.y) / tan(player->rotation_angle) ;
	if(!player->ray->left && adjacent_length > 0)//
		player->ray->colision_hor.x = player->pos.x + adjacent_length;//
	else//
		player->ray->colision_hor.x = player->pos.x - adjacent_length;//
	if(!player->ray->down)
		player->ray->colision_hor.y--;
	if(is_there_a_wall(&player->ray->colision_hor,map))
	{
		player->ray->distance_horizontal = ray_length(player->pos, player->ray->colision_hor);
		// draw_line(data, player->pos, player->ray->colision);//se pinta la linea hasta la colision
	}
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
			if((!is_there_a_wall(&player->ray->colision_hor,map)))
			{
				printf("pruebo\n");
				player->ray->colision_hor.x += step_x;
				player->ray->colision_hor.y += step_y;	
			}
			else
			{
				printf("encuentro colision\n");
				colision = 1;
				// draw_line(data, player->pos, player->ray->colision);
				player->ray->distance_horizontal = ray_length(player->pos, player->ray->colision_hor);
			}
		}
	}
}

int	draw_line(t_data *data, t_point pos_player, t_point pos_colision)
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
		my_mlx_pixel_put(data, pixel.x, pixel.y \
			, 0xFF0000);
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
	horizontal_colision(player, map/*, data*/);
	vertical_colision(player, map/*, data*/);
	if(player->ray->distance_horizontal < player->ray->distance_vertical)
		draw_line(data, player->pos, player->ray->colision_hor);
	else
		draw_line(data, player->pos, player->ray->colision_ver);
		
}

void	vertical_colision(t_player *player, t_map *map/*, t_data *data*/)
{
	float opposite_length;
	int step_x;
	int step_y;
	int colision;
	
	step_x = 0;
	step_y = 0;
	colision = 0;
	player->ray->colision_ver.x = floor(player->pos.x / map->tile_size) * map->tile_size;
	if(!player->ray->left)
		player->ray->colision_ver.x += map->tile_size;
	opposite_length =  (player->ray->colision_ver.x - player->pos.x) * (tan(player->rotation_angle));
	player->ray->colision_ver.y = player->pos.y + opposite_length;
	
	
	if(player->ray->left)
		player->ray->colision_ver.x--;
	if(is_there_a_wall(&player->ray->colision_ver,map))
		player->ray->distance_vertical = ray_length(player->pos, player->ray->colision_ver);
		// draw_line(data, player->pos, player->ray->colision);//se pinta la linea hasta la colision
	else
	{
		// se añade un step y se comprueba en bucle añadiendo steps
		//STEP
		step_x = map->tile_size;
		step_y = step_x * (tan(player->rotation_angle));
		if(player->ray->left)
			step_x = -step_x;
		if((!player->ray->down && step_y > 0) || (player->ray->down && step_y < 0))
			step_y = -step_y;
		while (!colision)
		{
			if(!is_there_a_wall(&player->ray->colision_ver,map))
			{
				player->ray->colision_ver.x += step_x;
				player->ray->colision_ver.y += step_y;	
			}
			else
			{
				colision = 1;
				player->ray->distance_vertical = ray_length(player->pos, player->ray->colision_ver);
				//draw_line(data, player->pos, player->ray->colision_ver);
			}
		}
	}
	
}

//Pitagoras to know the length of the ray
float	ray_length(t_point pos, t_point col)
{
	float	hypotenuse;
	float	x;
	float	y;

	if (pos.x > col.x)
		x = pos.x - col.x;
	else
		x = col.x - pos.x;
	if (pos.y > col.y)
		y = pos.y - col.y;
	else
		y = col.y - pos.y;

	hypotenuse = sqrt((x * x) + (y * y));
	return(hypotenuse);
}