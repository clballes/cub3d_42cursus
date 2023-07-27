/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:21:28 by albagarc          #+#    #+#             */
/*   Updated: 2023/07/27 15:27:51 by albagarc         ###   ########.fr       */
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