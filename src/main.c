#include "cub3d.h"
#include "../mlx/mlx.h"

void	init_game(void)
{
	t_all *all;
	
	all = malloc(1 * sizeof(t_all));
	if(!all)
		return;
	all->vars.mlx = mlx_init();
	all->vars.win = mlx_new_window(all->vars.mlx, WIN_X, WIN_Y, "Cub3d");
	all->data.img = mlx_new_image(all->vars.mlx, WIN_X, WIN_Y);
	all->data.addr = mlx_get_data_addr(all->data.img, &all->data.bits_per_pixel, \
		&all->data.line_length, &all->data.endian);
	mlx_hook(all->vars.win, 2, 0, key_press, &all->vars);
	mlx_hook(all->vars.win, 17, 0, ft_destroy_window, &all->vars);
	// mlx_hook(all.vars.win, 4, 0, ft_mouse_down, &all.vars);
	// mlx_hook(all.vars.win, 5, 0, ft_mouse_up, &all.vars);
	// mlx_hook(all.vars.win, 6, 0, ft_mouse_move, &all.vars);
	draw_initial_map(&all->data);
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->data.img, 0, 0);
	mlx_loop(all->vars.mlx);
}




int main(int argc, char **argv)
{
	(void)argv;
    if (argc > 2 || argc == 1)
        write(2, "just one .cub argument!\n", 24);
    else
    {
        if (init_parse(argv) != 0) //funcion q llama a otras para parsing mapa
            return (1); //parsing error encounter
		else
			init_game();
    }
    return (0);
}

