/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:44:48 by clballes          #+#    #+#             */
/*   Updated: 2023/07/31 16:44:49 by clballes         ###   ########.fr       */
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
			|| (ft_strncmp(element[i].id, "E", 2) == 0))
			check++;
	}
	if (check != 6)
		return (1);
	return (0);
}

int	parse_image_weight(char *path, int fd)
{
	(void)path;
	char *line;
	int i;

	i = 0;
	while(i < 3)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	line = get_next_line(fd);
	printf("la line es %s\n", line);
	free(line);
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
				write(2, "route doesn't exist\n", 20);
				return (1);
			}
			parse_image_weight(element[i].direction, fd);
		}
	}
	return (0);
}

int	parse_elements(t_element *element)
{
	if (check_id(element) != 0)
	{
		write(2, "error id name\n", 14);
		return (1);
	}
	if (check_path_direction(element) != 0)
		return (1);
	return (0);
}
