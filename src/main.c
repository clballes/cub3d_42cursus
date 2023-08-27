/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:20:24 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/27 19:40:09 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../mlx/mlx.h"

void	draw_image(t_all *all)
{
	//clear_map
	clear_map(all->data, &all->player);
	clear_render(all->data);
	update_variables(&all->player, &all->map);
	//pintaremos la imagen en 3d
	draw_render(all);
	//pintaremos el minimap
	draw_minimap_and_rays(all, all->data, &all->player);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, \
		all->data->img, 0, 0);
}

void	init_game(t_all *all)
{
	all->vars = ft_calloc(1, sizeof(t_vars));
	all->data = ft_calloc(1, sizeof(t_data));
	all->vars->mlx = mlx_init();
	all->vars->win = mlx_new_window(all->vars->mlx, WIN_X, WIN_Y, "Cub3d");
	all->data->img = mlx_new_image(all->vars->mlx, WIN_X, WIN_Y);
	all->data->addr = mlx_get_data_addr(all->data->img, \
		&all->data->bits_per_pixel, &all->data->line_length, \
		&all->data->endian);
	init_path_image(all->element, all);
	init_player(&all->player, &all->map);
	draw_image(all);
	mlx_hook(all->vars->win, 2, 0, key_press, all);
	mlx_hook(all->vars->win, 3, 0, key_up, &all->player);
	mlx_hook(all->vars->win, 17, 0, ft_destroy_window, all->vars);
	mlx_loop(all->vars->mlx);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	all = ft_calloc(1, sizeof(t_all));
	if (argc > 2 || argc == 1)
		write(2, "just one .cub argument!\n", 24);
	else
	{
		if (init_parse(argv, &all->map, all) != 0)
		{
			free(all);
			return (1);
		}
		else
			init_game(all);
	}
	return (0);
}

//FREEEEE
