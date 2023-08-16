/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:46:13 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/16 17:05:11 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, t_map *map)
{
	t_square	*square;
	
	square = ft_calloc(1, sizeof(t_square));
	player->square = square;
	player->first_orientation = map->player_orientation;
	if (map->player_orientation == 'N')
		player->rot_angle = 3 * M_PI_2;
	if (map->player_orientation == 'S')
		player->rot_angle =  M_PI_2;
	if (map->player_orientation == 'E')
		player->rot_angle = 2 * M_PI;
	if (map->player_orientation == 'W')
		player->rot_angle =  M_PI;
	player->advance = 0;
	player->rotate = 0;
	player->speed_adv = 3;
	player->speed_rot = 3 * (M_PI / 180);
	player->pos.x = map->pos_x * map->tile_size + map->tile_size / 2; //centro del cuadrado que pintamos_x
	player->pos.y = map->pos_y * map->tile_size + map->tile_size / 2; //centro del cuadrado que pintamos_y
	player->square->coord.x = player->pos.x  - (float)PLAYER/2;
	player->square->coord.y = player->pos.y  - (float)PLAYER/2;
	player->square->coord.color = 0xFFFFFF;
	init_ray(player);
}

void	init_path_image(t_element *element, t_all *all)
{
	int	i;

	i = -1;
	while(++i < 6)
	{
		if (ft_strncmp(element[i].id, "NO", 3) == 0)
			all->data->xpm_NO = mlx_xpm_file_to_image(all->vars->mlx,
			"./src/textures/a.xpm", &all->data->width, &all->data->height);
		if (ft_strncmp(element[i].id, "SO", 3) == 0)
			all->data->xpm_SO = mlx_xpm_file_to_image(all->vars->mlx,
				element[i].direction, &all->data->width, &all->data->height);
		if (ft_strncmp(element[i].id, "EA", 3) == 0)
			all->data->xpm_EA = mlx_xpm_file_to_image(all->vars->mlx,
				element[i].direction, &all->data->width, &all->data->height);
		if (ft_strncmp(element[i].id, "E", 2) == 0)
			all->data->xpm_E = mlx_xpm_file_to_image(all->vars->mlx,
				element[i].direction, &all->data->width, &all->data->height);
	}
}

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
}