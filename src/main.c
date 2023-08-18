#include "cub3d.h"
#include "../mlx/mlx.h"

void draw_image(t_all *all)
{
	//pintaremos la imagen en 3d
	
	//pintaremos el minimap
	draw_initial_map(all->data, &all->player, all, 1);
}

void	init_game(t_all *all)
{
	// t_all *all;
	// all = ft_calloc(1, sizeof(t_all));
	all->vars = ft_calloc(1, sizeof(t_vars));
	all->data = ft_calloc(1, sizeof(t_data));
	all->vars->mlx = mlx_init();
	all->vars->win = mlx_new_window(all->vars->mlx, WIN_X, WIN_Y, "Cub3d");
	all->data->img = mlx_new_image(all->vars->mlx, WIN_X, WIN_Y);
	all->data->addr = mlx_get_data_addr(all->data->img, &all->data->bits_per_pixel, \
		&all->data->line_length, &all->data->endian);
	init_path_image(all->element, all);
	draw_image(all);//esta funcion en verdad tiene que iniciar el minimap y el render inicial
	mlx_hook(all->vars->win, 2, 0, key_press, all);
	mlx_hook(all->vars->win, 3, 0, key_up, &all->player);
	mlx_hook(all->vars->win, 17, 0, ft_destroy_window, &all->vars);
	// mlx_hook(all.vars.win, 4, 0, ft_mouse_down, &all.vars);
	// mlx_hook(all.vars.win, 5, 0, ft_mouse_up, &all.vars);
	// mlx_hook(all.vars.win, 6, 0, ft_mouse_move, &all.vars);

	
	mlx_loop(all->vars->mlx);
}



int main(int argc, char **argv)

{
	t_all *all;

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
		{
			init_game(all);
			init_render(all);
		}
    }
    return (0);
}

