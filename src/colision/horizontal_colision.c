/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_colision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:06:34 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/17 11:12:42 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hcol_up(t_player *player, t_map *map)
{
	player->ray->colision_hor.y += ((int)(player->pos.y/map->tile_size) * map->tile_size) - 0.0001;
	player->ray->colision_hor.x = (player->pos.y - player->ray->colision_hor.y) / tan(player->rot_angle) + player->pos.x;
	// la tangente es negativa
}

// void hcol_up_left(t_player *player, t_map *map)
// {
// 	player->ray->colision_hor.y = ((int)(player->pos.y/map->tile_size) * map->tile_size) - 0.0001;
// 	player->ray->colision_hor.x = (player->pos.y - player->ray->colision_hor.y) / tan(player->rot_angle) + player->pos.x;
// 	// la tangente es positiva
// }

void hcol_down(t_player *player, t_map *map)
{
	player->ray->colision_hor.y += ((int)(player->pos.y/map->tile_size) * map->tile_size) + map->tile_size;
	player->ray->colision_hor.x = (player->ray->colision_hor.y - player->pos.y) / tan(player->rot_angle) + player->pos.x;
	//la tangente es positiva positivo entre positvo
}

// void hcol_down_left(t_player *player, t_map *map)
// {
// 	player->ray->colision_hor.y = ((int)(player->pos.y/map->tile_size) * map->tile_size) + map->tile_size;
// 	player->ray->colision_hor.x = (player->ray->colision_hor.y - player->pos.y) / tan(player->rot_angle) + player->pos.x;
// 	//la tangente es negativa. Positivo entre negativo 
// }

int	is_there_a_wall(t_point *point, t_map *map)
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
	// printf("X: %f Y: %f\n", point->x, point->y);
	// printf("M X: %f Y: %f\n", matrix.x, matrix.y);
	// for (int i = 0; i < map->rows; i++) {
	// 	for (int j = 0; j < map->cols; j++) {
	// 		if (i == (int)matrix.y && j == (int)matrix.x)
	// 			printf("#");
	// 		else
	// 			printf("%c", map->map_arr[i][j]);
	// 	}
	// 	printf("\n");
	// }
	if (map->map_arr[(int)matrix.y][(int)matrix.x] == '1')
	{
		printf("PARED\n");
		return (1);
	}
	
	return (0);
}

void	find_colision_with_horizontal_lines(t_player *player, t_map *map)
{
	if(player->rot_angle == 0 || player->rot_angle == M_PI)
	{
		printf("miro al este y no pinto\n");
		return ;
	}
	player->ray->colision_hor.x = 0;
	player->ray->colision_hor.y = 0;
	while(1)
	{
		if((player->rot_angle > M_PI  && player->rot_angle < 2 * M_PI))
		{
			printf("UP\n");
			hcol_up(player, map);
		}
		if((player->rot_angle > 0 && player->rot_angle < M_PI))
		{
			printf("DOWN\n");
			hcol_down(player,map);
		}
		printf("x=%f y=%f cols:%d\n",player->ray->colision_hor.x,player->ray->colision_hor.y,map->cols );
		if(!is_there_a_wall(&player->ray->colision_hor, map)&& player->ray->colision_hor.x / map->tile_size <= map->cols)
			{
				printf("?\n");
				if(player->ray->down)
					player->ray->colision_hor.y += map->tile_size;
				else
					player->ray->colision_hor.y -= map->tile_size;
				player->ray->colision_hor.x += (map->tile_size)/tan(player->rot_angle);
				printf("x=%f y=%f cols:%d\n",player->ray->colision_hor.x,player->ray->colision_hor.y,map->cols );
				
			}
		else
		{
			printf("hace el break\n");
			break;
		}
		
	}
}