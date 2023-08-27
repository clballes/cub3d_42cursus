/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_empty_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:44:47 by albagarc          #+#    #+#             */
/*   Updated: 2023/08/27 19:34:37 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Function that paints a pixel
int	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIN_X || y >= WIN_Y || x < 0 || y < 0)
		return (-1);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

//Function that paints a square. 
//You provide the point to start and the size of the side
void	paint_square(t_point *point, t_data *data, int square_side)
{
	double	x;
	double	y;

	y = point->y;
	while (y < point->y + square_side)
	{
		x = point->x;
		while (x < point->x + square_side)
		{
			my_mlx_pixel_put(data, x, y, point->color);
			x++;
		}
		y++;
	}
}

//Draw the squares of the map, walls and blanks
void	draw_walls_blanks(t_square *wall, t_data *data, int x, int y)
{
	wall->coord.x = x * wall->side;
	wall->coord.y = y * wall->side;
	paint_square(&wall->coord, data, wall->side);
}

//Draw the empty map
void	draw_map(t_data *data, t_all *all)
{
	int			i;
	int			j;
	t_square	*wall;

	wall = ft_calloc(1, sizeof(t_square));
	wall->side = MAP_X / all->map.cols;

	// wall->side = WIN_X / all->map.cols;
	i = -1;
	while (++i < all->map.rows)
	{
		j = 0;
		while (j < all->map.cols)
		{
			if (all->map.map_arr[i][j] == '1')
			{
				wall->coord.color = TURQUOISE;
				draw_walls_blanks(wall, data, j, i);
			}
			else
			{
				wall->coord.color = BLACK;
				draw_walls_blanks(wall, data, j, i);
			}
			j++;
		}
	}
}


//FREEEEE DEL WALL