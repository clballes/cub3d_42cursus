/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_colision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:04 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/18 12:39:04 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	 vcol_left(t_player *player, t_map *map)
{
	player->ray->colision_ver.x = ((int)(player->pos.x / map->tile_size) * map->tile_size) - 0.0001;
	// UP (la resta es negativa)(la tangente es positiva) la y nos tiene que dar mas pequena
	// DOWN(la resta es negativa)(la tangente es negativa) la y nos tiene que dar mas grande
	player->ray->colision_ver.y = (player->ray->colision_ver.x - player->pos.x) * tan(player->rot_angle) + player->pos.y;
	printf("LEFT::colision_x:%f colision_y:%f\n",player->ray->colision_ver.x,player->ray->colision_ver.y );
	printf("tang=%f\n", tan(player->rot_angle));
}

void	vcol_right(t_player *player, t_map *map)
{
	player->ray->colision_ver.x =((int)(player->pos.x / map->tile_size) * map->tile_size) + map->tile_size;
	player->ray->colision_ver.y = ((player->ray->colision_ver.x - player->pos.x) * tan(player->rot_angle)) + player->pos.y;
	printf("RIGHT::posicion_x:%f poisicion_y:%f\n",player->pos.x,player->pos.y);
	printf("RIGHT::colision_x:%f colision_y:%f\n",player->ray->colision_ver.x,player->ray->colision_ver.y );
	printf("tang=%f\n", tan(player->rot_angle));
}

void	find_colision_with_vertical_lines(t_player *player, t_map *map)
{
	printf("player->rot_angle:%f y tile_size:%d\n", player->rot_angle, map->tile_size);
	// if(player->rot_angle == (3 * M_PI / 2) || player->rot_angle == (M_PI / 2))
	// {
	// 	printf("A\n");
	// 	//distancia vertical maxima;
	// 	return ;
	// }
	if(player->rot_angle > (M_PI / 2) && player->rot_angle < (3 * M_PI / 2))
	{
		printf("izquierda\n");
		vcol_left(player, map);
	}
	if((player->rot_angle > (3 * M_PI / 2) || player->rot_angle < (M_PI / 2)))
	{
		printf("derecha\n");
		vcol_right(player, map);
	}
	while(1)
	{
		printf("siguientes\n");
		if(!is_there_a_wall(&player->ray->colision_ver, map) && player->ray->colision_ver.y / map->tile_size <= map->rows)
			{
				if(!player->ray->left)
				{
					//lejanas de la derecha dan mal;
					
					player->ray->colision_ver.x += map->tile_size;
					printf("expected y= %f\n", ((player->pos.x - player->ray->colision_hor.x ) * tan(player->rot_angle)) + player->pos.y);
					player->ray->colision_ver.y += map->tile_size * tan(player->rot_angle);
					printf("la y calculada da:%f\n",player->ray->colision_ver.y );
				}
				else
				{
					player->ray->colision_ver.x -= map->tile_size;
					player->ray->colision_ver.y += (-map->tile_size) * tan(player->rot_angle);
				}
			}
		else
		{
			printf("PARED::posicion_x:%f poisicion_y:%f\n",player->pos.x,player->pos.y);
			printf("PARED::colision_x:%f colision_y:%f\n",player->ray->colision_ver.x,player->ray->colision_ver.y );
			printf("encuentro PARED\n");
			break;
		}
	}
}