/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:37:14 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/29 19:59:51 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

# define MAP_X 240
# define MAP_Y 128
# define FOV 60
# define HALFFOV 30

# define TURQUOISE 	0x33b3a6
# define BLACK		0x000000
# define WHITE		0xFFFFFF
# define RED		0xFF0000

typedef struct s_map	t_map;

typedef struct s_point
{
	double		x;
	double		y;
	int			color;

}	t_point;

//length: size of each ray, the smallest between horizontal or vertical
//t_point *colision: pointer to the colision point.
//char c: Indicates if the colision was with a horizontal or a vertical line
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

//char *id: identifies NO, SO, WE, EA, F, C
typedef struct s_element 
{
	char		*id;
	char		*direction;
	int			r;
	int			g;
	int			b;
	int			color;
}	t_element;

//int advance: 0 = parado ; 1 = adelante -1 = atras
//int rotate: 1 = derecha ; -1 = izquierda 
//rot_angle: N = pi/2 ; S = 3pi/2 ; E = pi ; W = 2pi  
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
}	t_player;

typedef struct s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}		t_data;

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
}	t_map;

typedef struct s_all {
	t_player	player;
	t_vars		*vars;
	t_map		map;
	t_data		*data;
	t_element	*element;
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
void	init_delta(t_map *map);
int		backtrack(char **map_arr, int row, int col, t_map *map);
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
int		is_valid_tile_for_player(double x, double y, t_map *map, \
t_player *player);
void	clear_render(t_data *data);

// void	init_ray(t_player	*player);
int		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	calculate_colisions(t_player *player, t_map *map);
void	paint_rays(t_player *player, t_data *data, int color);
double	grades_to_rads(double angle);

//colision
float	ray_length(t_point pos, t_point col);
int		is_there_a_wall(t_point *point, t_map *map, t_ray *ray);
void	colision_with_horizontal_lines(t_player *player, t_map *map, \
t_ray *ray);
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

#endif
