/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:44:48 by clballes          #+#    #+#             */
/*   Updated: 2023/09/13 16:22:56 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_id(t_element *element)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (++i < 6)
	{
		if ((ft_strncmp(element[i].id, "NO", 3) == 0)
			|| (ft_strncmp(element[i].id, "SO", 3) == 0)
			|| (ft_strncmp(element[i].id, "EA", 3) == 0)
			|| (ft_strncmp(element[i].id, "F", 2) == 0)
			|| (ft_strncmp(element[i].id, "C", 2) == 0)
			|| (ft_strncmp(element[i].id, "WE", 3) == 0))
			check++;
	}
	if (check != 6)
	{
		return (1);
	}
	return (0);
}

int	ft_res(char *line)
{
	char	*res;
	char	*res2;
	int		result;
	int		result2;

	res = ft_substr(line, 1, 3);
	result = ft_atoi(res);
	free(res);
	res2 = ft_substr(line, 4, 2);
	result2 = ft_atoi(res2);
	free(res2);
	free(line);
	if (result > 64 || result2 > 64)
	{
		write(2, "the size of the image is too heavy\n", 35);
		return (1);
	}
	return (0);
}

int	parse_image_weight(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 3)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			return (1);
		}
		free(line);
		i++;
	}
	line = get_next_line(fd);
	if (ft_res(line) != 0)
		return (1);
	return (0);
}

int	check_path_direction(t_element *element)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < 6)
	{
		if (!((ft_strncmp(element[i].id, "F", 2) == 0)
				|| (ft_strncmp(element[i].id, "C", 2) == 0)))
		{
			fd = open(element[i].direction, O_RDONLY);
			if (fd == -1)
			{
				write(2, "error: cannot open the route texture\n", 37);
				return (1);
			}
			if (parse_image_weight(fd) != 0)
			{
				close(fd);
				write(2, "error: cannot open the route texture\n", 37);
				return (1);
			}
			close(fd);
		}
	}
	return (0);
}

int	parse_elements(t_element *element)
{
	if (check_id(element) != 0)
	{
		write(2, "error: missing textures!\n", 25);
		return (1);
	}
	if (check_path_direction(element) != 0)
		return (1);
	return (0);
}
