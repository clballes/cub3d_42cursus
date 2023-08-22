/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/22 13:11:05 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
double	grades_to_rads(double angle);
//This function tell us the direction of the ray depending on the angle
// of the player.
void	direction_ray(t_player *player, t_ray *ray)
{
	ray->down = 0;
	ray->left = 0;
	if (player->ray_rot_angle < M_PI)
		ray->down = 1;
	if (player->ray_rot_angle > M_PI / 2 && player->ray_rot_angle < 3 * M_PI / 2)
		ray->left = 1;
}

//Check the intersection points of the grid.
//Sometimes we had to adjust this point with a 0.0001 accuracy,
// so we check those intersections as well.
//if we find a colision  in two intersections we have corner colision. 
int	check_colision_corner(t_point *point, t_map *map, t_ray *ray, t_point *matrix)
{
	int i;

	i = 0;
	if(((int)point->x % map->tile_size == 0 && \
	(int)(point->y) % map->tile_size == 0) || \
	((int)(point->x + 0.0001) % map->tile_size == 0 && \
	(int)(point->y + 0.0001) % map->tile_size == 0))
	{
		if(ray->down && map->map_arr[(int)matrix->y - 1][(int)matrix->x] == '1')
			i++;
		if(!ray->left && map->map_arr[(int)matrix->y][(int)matrix->x - 1] == '1')
			i++;
		if(!ray->down && map->map_arr[(int)matrix->y + 1][(int)matrix->x] == '1')
			i++;
		if(ray->left && map->map_arr[(int)matrix->y][(int)matrix->x + 1] == '1')
			i++;
	}
	if(i == 2)
		return(1);
	return(0);
}

// This function returns 1 if there is a wall in the point that is receiving.
int	is_there_a_wall(t_point *point, t_map *map, t_ray *ray)
{
	t_point	matrix;
	
	matrix.x = point->x / map->tile_size;
	matrix.y = point->y / map->tile_size;
	if (matrix.x >= map->cols)
		matrix.x = map->cols - 1;
	if (matrix.x <= 0)
		matrix.x = 0;
	if (matrix.y >= map->rows)
		matrix.y = map->rows - 1;
	if (matrix.y <= 0)
		matrix.y = 0;	
	if(check_colision_corner(point, map, ray, &matrix))
		return(1);
	// for (int j = 0; j < map->rows; j++) {
	// 	for (int i = 0; i < map->cols; i++) {
	// 		if (j == (int)matrix.y && i == (int)matrix.x)
	// 			printf("\x1b[31m%c\x1b[0m", map->map_arr[j][i]);
	// 		else
	// 			printf("%c", map->map_arr[j][i]);
	// 	}
		// printf("\n");
	// }
	if (map->map_arr[(int)matrix.y][(int)matrix.x] == '1')
		return (1);
	return (0);
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
			, pos_colision.color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels = pixels - 1;
	}
	return (1);
}

void	set_angles_for_rays(t_player *player)
{
	double initial_ray_rot_angle;

	player->angle_increase = grades_to_rads((double)FOV / (double)WIN_X);
	initial_ray_rot_angle = player->rot_angle - grades_to_rads((double)HALFFOV);
	angle(&initial_ray_rot_angle);
	player->ray_rot_angle = initial_ray_rot_angle;
}
void paint_rays(t_player *player, t_data *data, int color)
{
	int i;

	i = 0;
	if(player->ray[i].colision == NULL)
	{
		printf("primer\n");
		return;
	}
	// if(color == 0xFF0000)
		// exit(1);
	printf("segun col%p hor%p ver%p\n", player->ray[i].colision, &player->ray[i].colision_hor, &player->ray[i].colision_ver);
	while(i < WIN_X)
	{
		// printf("i%p \n", player->ray[i].colision);
		player->ray[i].colision->color = color;
		draw_line(data, player->pos, *player->ray[i].colision);
		// printf("peto %d x:%f, y:%f,\n", i, player->ray[i].colision->x, player->ray[i].colision->y);
		i++;
	}
	
}
// Compare the vertical and the horizontal colision and draw 
// the rays that are shorter.
void	calculate_colisions(t_player *player, t_map *map, t_data *data/*, int color*/)
{
	int i;
	(void)data;
	set_angles_for_rays(player);
	
	i = 0;
	while(i < WIN_X)
	{
		// player->ray[i].colision_hor.color = color;
		// player->ray[i].colision_ver.color = color;
		direction_ray(player,&player->ray[i]);
		find_colision_with_horizontal_lines(player, map, &player->ray[i]);
		find_colision_with_vertical_lines(player, map, &player->ray[i]);
		if (player->ray[i].distance_horizontal < player->ray[i].distance_vertical)
		{
			// draw_line(data, player->pos, player->ray[i].colision_hor);
			player->ray[i].colision = &player->ray[i].colision_hor;
			player->ray[i].length = player->ray[i].distance_horizontal;
		}
		else
		{
			player->ray[i].colision = &player->ray[i].colision_ver;
			// draw_line(data, player->pos, player->ray[i].colision_ver);
			player->ray[i].length = player->ray[i].distance_vertical;
		}
		player->ray_rot_angle += player->angle_increase;
		angle(&player->ray_rot_angle);
		i++;
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
	return (hypotenuse);
}

double	grades_to_rads(double angle)
{
	angle = angle * M_PI / 180;
	return (angle);
}