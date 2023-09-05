/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:17:57 by albagarc          #+#    #+#             */
/*   Updated: 2023/09/05 19:18:25 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_tx(double x, double y, char c)
{
	double	result;

	result = 0;
	if (c == 'h')
		result = (int)x % 64;
	else
		result = (int)y % 64;
	return (result);
}

double	calculate_ty(double altura_muro, int j)
{
	double	result;
	double	y;

	if (altura_muro < 0)
		altura_muro = altura_muro * (-1);
	result = 64 / altura_muro;
	y = j * result;
	return (y);
}

//gets the texture correct return the
//xpm where is it stored the values from the texture
t_data	find_texture( t_all *all, t_ray *ray)
{
	t_data	img_xpm;

	if (ray->down && ray->c == 'h')
		img_xpm = all->xpm_so;
	else if (!ray->down && ray->c == 'h')
		img_xpm = all->xpm_no;
	else if (ray->left && ray->c == 'v')
		img_xpm = all->xpm_we;
	else
		img_xpm = all->xpm_ea;
	return (img_xpm);
}
