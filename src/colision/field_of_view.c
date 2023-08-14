/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_of_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:55:54 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/14 16:28:09 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	grades_to_rads(double angle)
{
	angle = angle * M_PI / 180;
	return (angle);
}



// void	draw_fov_rays(t_player *player, t_map *map, t_data *data)
// {
// 	// (void)data;
// 	// (void)map;
// 	// double	angle_increase;
// 	// double initial_ray_rot_angle;
// 	// int i;

// 	// i = 0;
// 	// angle_increase = grades_to_rads(FOV / WIN_X);
// 	// initial_ray_rot_angle = player->rot_angle - grades_to_rads(HALFFOV);
// 	// angle(&initial_ray_rot_angle);
// 	// player->ray_rot_angle = initial_ray_rot_angle;
// 	// printf("ray_Rot_angle: %f\n", initial_ray_rot_angle);
// 	paint_ray(player, map, data);
// 	// while (i < FOV)
// 	// {
// 	// 	printf("eyyy\n");
// 	// 	paint_ray(player, map, data);
// 	// 	player->ray_rot_angle += angle_increase;
// 	// 	i++;
// 	// }
	
// }