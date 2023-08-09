/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:46:13 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/09 15:34:39 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, int orientation, int x, int y, int tile_size)
{
	t_square *square;
	
	square = ft_calloc(1, sizeof(t_square));
	player->square = square;
	
	//  player->square->side = tile_size;
	player->first_orientation = orientation;
	if (orientation == 'N')
		player->rotation_angle = 3 * M_PI_2;
	if (orientation == 'S')
		player->rotation_angle =  M_PI_2;
	if (orientation == 'E')
		player->rotation_angle = 2 * M_PI;
	if (orientation == 'W')
		player->rotation_angle =  M_PI;
	player->advance = 0;
	player->rotate = 0;
	player->speed_adv = 1;
	player->speed_rot = 3 * (M_PI / 180);
	// printf("al inicio speed_rot = %f\n", player->speed_rot);
	player->pos.x = x + tile_size / 2; //centro del cuadrado que pintamos_x
	player->pos.y = y + tile_size / 2; //centro del cuadrado que pintamos_y
	player->square->side = tile_size/10;
	player->square->coord.x = x + tile_size / 2 - (tile_size / 20);
	player->square->coord.y = y + tile_size / 2 - (tile_size / 20);
	// printf("init_x:%d, init_y:%d\n", player->square->coord.x, player->square->coord.y );
	player->square->coord.color = 0xFFFFFF;

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
