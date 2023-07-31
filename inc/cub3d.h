

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

# define WIN_X 400
# define WIN_Y 400

# define TURQUOISE 0x33b3a6

typedef struct s_ray
{
	int colision_x;
	int colision_y;

	//ray direction
	int down;
	int left;

	//crash
	int horizontal_crash;
	int vertical_crash;

}	t_ray;
typedef struct s_square
{
	int x;
	int y;
	int color;
	int side;
}	t_square;

typedef struct s_corners
{
	int up_left_x;
	int up_left_y;
	int up_right_x;
	int up_right_y;
	int down_left_x;
	int down_left_y;
	int down_right_x;
	int down_right_y;

}	t_corners;
typedef struct s_element //esto sera un array que guardaremos la info de los elementos de texto del mapa
{
    char *id; //identifier NO, SO, WE, EA, F, C
    char *direction; // direction or colors
    // t_map *map; //puntero a estructura del mapa con los numeros ltras, esto nose
}           t_element;

typedef struct s_player
{
	t_square	*square;
	t_ray		*ray;
    int		pos_x;
	int		pos_y;
	int		tile_size;
	double 	first_orientation;
	int 	advance; // 0 = parado ; 1 = adelante -1 = atras
	int 	rotate; // 1 = derecha ; -1 = izquierda 
	double 	rotation_angle; // N = pi/2 ; S = 3pi/2 ; E = pi ; W = 2pi 
	int 	speed_adv; // 3pixels
	double 	speed_rot; // GRADOS //cuantos grados va a girar cada vez que le damos  3 * (pi / 180) // pi / 180 es cuantos radianes es un grado

	
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
	int 		tile_size;
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
	t_player 	player;
	t_vars		*vars;
	t_map		map;
	t_data		*data;

}	t_all;

//parsing map
int		init_parse(char **argv);
int		elements_arr(t_element *element, int fd);
int		ft_digit(char *str);
int 	init_map(t_map *map, int fd); //hacemos open del map y guardamos en estructura el mapa, que llamara otras funciones check errores
int		search_pos(t_map *map);
// void    create_arr(t_map *map, int fd);
int		ft_destroy_window(t_vars *vars);

int		key_press(int keycode, t_all *all);
int		key_up(int keycode, t_player *player);
void	draw_initial_map(t_data *data, t_player *player, t_all *all);
void	init_player(t_player *player, int orientation, int x, int y, int tile_size);
// int		movements(int keycode, t_player *player);
void	update_map(t_player *player, t_map *map, t_data *data, t_all *all);

int	is_valid_tile(t_player *player, int x, int y);

#endif



