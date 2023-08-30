#ifndef CUB_3D_H
# define CUB_3D_H

# include "libft.h"
# include "get_next_line.h"
# include "../mlx/mlx.h"
# include "keycode_hook.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

# define WIN_X 1920
# define WIN_Y 1024
# define MAP_X WIN_X / 8
# define MAP_Y WIN_Y / 8
# define FOV 60
# define HALFFOV 30
# define TURQUOISE 	0x33b3a6
# define BLACK		0x000000
# define WHITE		0xFFFFFF
# define RED		0xFF0000

typedef struct s_map	t_map;

typedef struct s_render
{
	double	tx;
	double	ty;
	int		start;
	int		end;
	double	plano_proyeccion;
	double	distance;
	double	altura_muro;
}			t_render;

typedef struct s_point
{
	double		x;
	double		y;
	int			color;

}				t_point;

//la colision es el punto de colision de cada rayo
//la laength la length del rayo hasta q choca contra la colision
typedef struct s_ray
{
	t_point		col_hor;
	t_point		col_ver;
	double		dist_hor;
	double		dist_ver;
	int			down;
	int			left;
	double		length;
	t_point		*colision;
	double		each_ray_angle;
	char		c;
}	t_ray;

typedef struct s_square
{
	t_point		coord;
	int			side;
}	t_square;

typedef struct s_corners
{
	int			up_left_x;
	int			up_left_y;
	int			up_right_x;
	int			up_right_y;
	int			down_left_x;
	int			down_left_y;
	int			down_right_x;
	int			down_right_y;
}	t_corners;

//esto sera un array que guardaremos la info de los elementos de texto del mapa
typedef struct s_element
{
	char		*id;
	char		*direction;
	int			r;
	int			g;
	int			b;
	int			color;
}				t_element;

//  //	0= parado ; 1 = adelante -1 = atras - advance
// // 1 = derecha ; -1 = izquierda  rotate
// N = pi/2 ; S = 3pi/2 ; E = pi ; W = 2pi - rot angle
// 3pixels
// GRADOS  3 * (pi / 180) // pi / 180
typedef struct s_player
{
	t_square	*square;
	t_ray		*ray;
	t_point		pos;
	double		first_orientation;
	int			advance;
	int			rotate;
	double		rot_angle;
	int			speed_adv; 
	double		speed_rot;
	double		ray_angle;
	double		angle_increase;
	double		player_size;
}				t_player;

typedef struct s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_data;

typedef struct s_vars{
	void		*mlx;
	void		*win;
}	t_vars;

typedef struct s_map
{
	int			tile;
	char		**map_arr;
	char		**copy_map;
	char		*map_unid;
	int			cols;
	int			delta_row[4];
	int			delta_col[4];
	int			next_row;
	int			next_col;
	int			pos_y;
	int			pos_x;
	int			rows;
	int			player_orientation;
}				t_map;

typedef struct s_all {
	t_player	player;
	t_vars		*vars;
	t_map		map;
	t_data		*data;
	t_element	*element;
	t_render	render;
	t_data		xpm_no;
	t_data		xpm_so;
	t_data		xpm_ea;
	t_data		xpm_we;
}	t_all;

//parsing map
int		init_parse(char **argv, t_map *map, t_all *all);
int		init_elements(t_element *element, int fd);
int		init_map(t_element *element, int fd, t_map *map);
int		ft_digit(char *str);
int		search_pos(t_map *map);
void	copy_map(t_map *map);
int		parse_elements(t_element *element);
void	init_path_image(t_element *element, t_all *all);
int		convert_rgb_hex(t_element *element);

// int		map_closed(t_map *map, int playerRow, int playerCol);
void	init_delta(t_map *map);
int		backtrack(char **map_arr, int row, int col, t_map *map);

// void    create_arr(t_map *map, int fd);
int		ft_destroy_window(t_vars *vars);

//events
int		key_press(int keycode, t_all *all);
int		key_up(int keycode, t_player *player);

//free functions
void	free_arr(char **copy_map, int rows);
void	free_elements(t_element *element);
void	free_all(t_map *map, t_element *element, int i);
char	*free_var(char *src, char *dest);

//render witnodw
void	init_render(t_all *all);
int		is_valid_tile_for_player(double x, double y,
			t_map *map, t_player *player);
void	clear_render(t_data *data);

// void	init_ray(t_player	*player);
int		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	calculate_colisions(t_player *player, t_map *map);
void	paint_rays(t_player *player, t_data *data, int color);
double	grades_to_rads(double angle);

//colision
float	ray_length(t_point pos, t_point col);
int		is_there_a_wall(t_point *point, t_map *map, t_ray *ray);
void	colision_with_horizontal_lines(t_player *player,
			t_map *map, t_ray *ray);
void	colision_with_vertical_lines(t_player *player, t_map *map, t_ray *ray);
void	angle(double *angle);
void	direction_ray(t_player *player, t_ray *ray);
void	set_ray_colision(t_ray *ray, char c);

//draw_minimap
void	clear_map( t_data *data, t_player *player);
void	draw_map(t_data *data, t_all *all);
void	draw_minimap_and_rays(t_all *all, t_data *data, t_player *player);
void	paint_square(t_point *point, t_data *data, int square_side);

//draw_everything
void	init_player(t_player *player, t_map *map);
void	update_variables(t_player *player, t_map *map);
void	draw_image(t_all *all);
void	draw_render(t_all *all);
double	calculate_tx(double x, double y, char c);
double	calculate_ty(double alturaMuro, int j);
t_data	find_texture(t_all *all, t_ray *ray);
#endif
