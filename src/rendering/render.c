/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:07:39 by clballes          #+#    #+#             */
/*   Updated: 2023/07/31 19:07:41 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Changes pixel of given image to given color
*/
static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

/**
 * Returns color of pixel in pos(x,y)
*/
int	img_pix_get(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(int *)pixel);
}

/**
 * Changes pixel of game image to given color
 * Checks x and y are within window limits
*/
// void	draw_pixel(t_master *master, int x, int y, int color)
// {
// 	if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
// 		img_pix_put(&master->mlx.img, x, y, color);
// }

int	init_render(t_all *all)
{
	int	distance_proyec;
	int	height_wall;
	int distance = 80; //(all->ray->distance)
	int	i;

	i = 0;
	distance_proyec = (WIN_Y / 2) / tan(ANGULO/2);
	printf("la dis es %d\n", distance_proyec);
	height_wall = (WIN_Y / distance) * distance_proyec;
	printf("la wall height  es %d\n", height_wall);
	//calculamos la linea
	int y0 = (WIN_Y / 2) - (height_wall / 2); //punto donde empezamos a poner pixel de color
	printf("el y0 es %d\n", y0);
	int y1 = y0 + height_wall;
	printf("el y1 es %d\n", y1);
    // int win_width = 500;
    // int win_height = 500;
    // int img_width = 10; // Width of the part of the image you want to display
    // int img_height = 10; // Height of the part of the image you want to display

    // Define the position to display the image within the window
    int x = 200;
    int y = 200;
	int pixget = img_pix_get(&text, 4, 4);
    // Display the part of the image on the window
    img_pix_put(all->data.img, x, y, pixget);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->data->xpm_NO, x, y);

    return (0);
}
