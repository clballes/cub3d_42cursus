/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:59:30 by clballes          #+#    #+#             */
/*   Updated: 2023/09/13 16:21:31 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_ifdigit(char *str, int rgb)
{
	if (ft_digit(str) != 0)
	{
		free(str);
		return (-1);
	}
	rgb = ft_atoi(str);
	free(str);
	if (rgb > 255 || rgb < 0)
	{
		write(2, "error: RGB numbers between 0 and 255\n", 37);
		return (-1);
	}
	return (0);
}

int	check_colors(char *direction, char *str, int rgb)
{
	int		i;
	int		start;
	int		len;
	int		j;

	j = 0;
	start = 0;
	i = -1;
	while (++i <= (int)ft_strlen(direction))
	{
		if (direction[i] == ',' || direction[i] == '\0')
		{
			j++;
			len = i - start;
			str = ft_substr(direction, start, len);
			if (check_ifdigit(str, rgb) != 0)
				return (-1);
			start = i + 1;
		}
	}
	if (j != 3)
		return (-2);
	return (0);
}

int	parse_colors(t_element *element)
{
	int		i;
	int		res_c;
	int		res_f;
	char	*str;
	int		rgb;

	i = 0;
	rgb = 0;
	str = NULL;
	while (i < 6)
	{
		if (ft_strncmp(element[i].id, "F", 2) == 0)
			res_f = check_colors(element[i].direction, str, rgb);
		if (ft_strncmp(element[i].id, "C", 2) == 0)
			res_c = check_colors(element[i].direction, str, rgb);
		i++;
	}
	if (res_f == -1 || res_c == -1)
		return (1);
	if (res_f == -2 || res_c == -2)
	{
		write(2, "error: check we have 3 numbers for RGB\n", 39);
		return (1);
	}
	return (0);
}

int	init_elements(t_element *element, int fd)
{
	if (elements_arr(element, fd) != 0)
	{
		free_elements(element);
		write(2, "Error: missing route\n", 21);
		return (1);
	}
	if ((parse_elements(element) != 0) || (parse_colors(element) != 0)
		|| (convert_rgb_hex(element) != 0))
	{
		free_elements(element);
		return (1);
	}
	return (0);
}
