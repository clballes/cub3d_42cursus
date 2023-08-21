/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_colision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:04 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/21 16:27:35 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	 vcol_left(t_player *player, t_map *map, t_ray *ray)
{
	ray->colision_ver.x = ((int)(player->pos.x / map->tile_size) * map->tile_size) - 0.0001;
	ray->colision_ver.y = (ray->colision_ver.x - player->pos.x) * tan(player->ray_rot_angle) + player->pos.y;
	// printf("LEFT::colision_x:%f colision_y:%f\n",player->ray->colision_ver.x,player->ray->colision_ver.y );
	// printf("tang=%f\n", tan(player->rot_angle));
}

void	vcol_right(t_player *player, t_map *map, t_ray *ray)
{
	ray->colision_ver.x =((int)(player->pos.x / map->tile_size) * map->tile_size) + map->tile_size;
	ray->colision_ver.y = ((ray->colision_ver.x - player->pos.x) * tan(player->ray_rot_angle)) + player->pos.y;
	// printf("RIGHT::posicion_x:%f poisicion_y:%f\n",player->pos.x,player->pos.y);
	// printf("RIGHT::colision_x:%f colision_y:%f\n",player->ray->colision_ver.x,player->ray->colision_ver.y );
	// printf("tang=%f\n", tan(player->rot_angle));
}

void	find_colision_with_vertical_lines(t_player *player, t_map *map, t_ray *ray)
{
	if(player->ray_rot_angle > (M_PI / 2) && player->ray_rot_angle < (3 * M_PI / 2))
	{

		vcol_left(player, map, ray);
	}
	if((player->ray_rot_angle > (3 * M_PI / 2) || player->ray_rot_angle < (M_PI / 2)))
	{

		vcol_right(player, map, ray);
	}
	while(1)
	{
		if(!is_there_a_wall(&ray->colision_ver, map, ray) && ray->colision_ver.y / map->tile_size <= map->rows &&  ray->colision_ver.y / map->tile_size >= 0)
			{
				if(!ray->left)
				{

					ray->colision_ver.x += map->tile_size;
					ray->colision_ver.y += map->tile_size * tan(player->ray_rot_angle);

				}
				else
				{
					ray->colision_ver.x -= map->tile_size;
					ray->colision_ver.y += (-map->tile_size) * tan(player->ray_rot_angle);
				}
			}
		else
		{
			//Calculamos distancia
			ray->distance_vertical = ray_length(player->pos, ray->colision_ver);
			// printf("PARED::posicion_x:%f poisicion_y:%f\n",player->pos.x,player->pos.y);
			// printf("PARED::colision_x:%f colision_y:%f\n",player->ray->colision_ver.x,player->ray->colision_ver.y );
			// printf("encuentro PARED\n");
			break;
		}
	}
}