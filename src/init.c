/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:46:13 by albagarc          #+#    #+#             */
/*   Updated: 2023/09/05 19:15:18 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//si algo falla FREEE calloc the los rayos calloc del square
//Inits all the variables of the player struct
void	init_player(t_player *player, t_map *map)
{
	t_square	*square;

	map->tile = WIN_X / map->cols;
	player->player_size = map->tile / 5;
	square = ft_calloc(1, sizeof(t_square));
	player->square = square;
	player->first_orientation = map->player_orientation;
	if (map->player_orientation == 'N')
		player->rot_angle = 3 * M_PI_2;
	if (map->player_orientation == 'S')
		player->rot_angle = M_PI_2;
	if (map->player_orientation == 'E')
		player->rot_angle = 2 * M_PI;
	if (map->player_orientation == 'W')
		player->rot_angle = M_PI;
	player->advance = 0;
	player->rotate = 0;
	player->speed_adv = 10;
	player->speed_rot = 3 * (M_PI / 180);
	player->pos.x = map->pos_x * map->tile + map->tile / 2;
	player->pos.y = map->pos_y * map->tile + map->tile / 2;
	player->square->coord.x = player->pos.x - player->player_size / 2;
	player->square->coord.y = player->pos.y - player->player_size / 2;
	player->square->coord.color = 0xFFFFFF;
	player->ray = ft_calloc(WIN_X, sizeof(t_ray));
}

void	dinamic_addr(t_all *all, t_data *xpm, char *direc)
{
	xpm->img = mlx_xpm_file_to_image(all->vars->mlx, \
	direc, &all->data->width, &all->data->height);
	xpm->addr = mlx_get_data_addr(xpm->img, \
	&xpm->bits_per_pixel, &xpm->line_length, \
	&xpm->endian);
}

void	init_path_image(t_element *element, t_all *all)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (ft_strncmp(element[i].id, "NO", 3) == 0)
			dinamic_addr(all, &all->xpm_no, element[i].direction);
		if (ft_strncmp(element[i].id, "SO", 3) == 0)
			dinamic_addr(all, &all->xpm_so, element[i].direction);
		if (ft_strncmp(element[i].id, "EA", 3) == 0)
			dinamic_addr(all, &all->xpm_ea, element[i].direction);
		if (ft_strncmp(element[i].id, "WE", 3) == 0)
			dinamic_addr(all, &all->xpm_we, element[i].direction);
	}
}
