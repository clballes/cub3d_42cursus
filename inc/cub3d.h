

#ifndef CUB_3D_H
# define CUB_3D_H

#include "libft.h"
#include "get_next_line.h"
#include "../mlx/mlx.h"
#include "keycode_hook.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

# define WIN_X 1920
# define WIN_Y 1080

typedef struct s_element //esto sera un array que guardaremos la info de los elementos de texto del mapa
{
    char *id; //identifier NO, SO, WE, EA, F, C
    char *direction; // direction or colors
    // t_map *map; //puntero a estructura del mapa con los numeros ltras, esto nose
}           t_element;

typedef struct s_player
{
    int	pos_x;
	int	pos_y;
	
} t_player;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_vars{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_map
{
    char **map_arr;
	char *map_unid;
    int	max_x;
    int	max_y;
    int	pos_y;
    int	pos_x;
	int rows;
	t_element *element; //puntero a estructura array del texto
} t_map;

typedef struct s_all {
	t_vars	vars;
	t_map	map;
	t_data	data;
}	t_all;

//parsing map
int		init_parse(char **argv);
int		elements_arr(t_element *element, int fd);
int		ft_digit(char *str);
int 	init_map(t_map *map, int fd); //hacemos open del map y guardamos en estructura el mapa, que llamara otras funciones check errores
int		search_pos(t_map *map);
// void    create_arr(t_map *map, int fd);
int		ft_destroy_window(t_vars *vars);

int	key_press(int keycode, t_vars *vars);

#endif



