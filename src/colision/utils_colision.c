/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:44:10 by albagarc          #+#    #+#             */
/*   Updated: 2023/09/05 18:34:55 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	corner_colision(t_point *point, t_map *map, t_ray *ray, t_point *mtx);

// This function returns 1 if there is a wall in the point that is receiving.
int	is_there_a_wall(t_point *point, t_map *map, t_ray *ray)
{
	t_point	mtx;

	mtx.x = point->x / map->tile;
	mtx.y = point->y / map->tile;
	if (mtx.x >= map->cols)
		mtx.x = map->cols - 1;
	if (mtx.x <= 0)
		mtx.x = 0;
	if (mtx.y >= map->rows)
		mtx.y = map->rows - 1;
	if (mtx.y <= 0)
		mtx.y = 0;
	if (corner_colision(point, map, ray, &mtx))
		return (1);
	if (map->map_arr[(int)mtx.y][(int)mtx.x] == '1')
		return (1);
	return (0);
}

//Check the intersection points of the grid.
//Sometimes we had to adjust this point with a 0.0001 accuracy,
// so we check those intersections as well.
//if we find a colision  in two intersections we have corner colision. 
int	corner_colision(t_point *point, t_map *map, t_ray *ray, t_point *mtx)
{
	int	i;

	i = 0;
	if (((int)point->x % map->tile == 0 && \
		(int)(point->y) % map->tile == 0) || \
		((int)(point->x + 0.0001) % map->tile == 0 && \
		(int)(point->y + 0.0001) % map->tile == 0))
	{
		if (ray->down && map->map_arr[(int)mtx->y - 1][(int)mtx->x] == '1')
			i++;
		if (!ray->left && map->map_arr[(int)mtx->y][(int)mtx->x - 1] == '1')
			i++;
		if (!ray->down && map->map_arr[(int)mtx->y + 1][(int)mtx->x] == '1')
			i++;
		if (ray->left && map->map_arr[(int)mtx->y][(int)mtx->x + 1] == '1')
			i++;
	}
	if (i == 2)
		return (1);
	return (0);
}

//This function tell us the direction of the ray depending on the angle
// of the player.
void	direction_ray(t_player *player, t_ray *ray)
{
	ray->down = 0;
	ray->left = 0;
	if (player->ray_angle < M_PI)
		ray->down = 1;
	if (player->ray_angle > M_PI / 2 && player->ray_angle < 3 * M_PI / 2)
		ray->left = 1;
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

//Set the variables for a ray depending on if it is horizontal or vertical
void	set_ray_colision(t_ray *ray, char c)
{
	if (c == 'h')
	{
		ray->colision = &ray->col_hor;
		ray->length = ray->dist_hor;
		ray->c = 'h';
	}
	if (c == 'v')
	{
		ray->colision = &ray->col_ver;
		ray->length = ray->dist_ver;
		ray->c = 'v';
	}
}
