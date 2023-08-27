/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:59:30 by clballes          #+#    #+#             */
/*   Updated: 2023/07/24 19:59:34 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_colors(char *direction, char *str, int rgb)
{
	int		i;
	int		start;
	int		len;

	start = 0;
	i = -1;
	
	while (++i <= (int)ft_strlen(direction))
	{
		if (direction[i] == ',' || direction[i] == '\0')
		{
			len = i - start;
			str = ft_substr(direction, start, len);
			if (ft_digit(str) != 0)
			{
				free(str);
				return (-1);
			}
			rgb = ft_atoi(str);
			free(str);
			if (rgb > 255 || rgb < 0)
				return (-1);
			start = i + 1;
		}
	}
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
	return (0);
}

void	element_dir(t_element *element, char *line, int i)
{
	int	len;

	element[i].direction = line + 2; 
	element[i].direction = ft_strtrim(element[i].direction, " ");
	len = ft_strlen(element[i].direction);
	element[i].direction[len] = '\0';
}

void	elements_arr(t_element *element, int fd)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	line = get_next_line(fd);
	while (i < 6)
	{
		while (ft_strlen(line) == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		element[i].id = line;
		j = 0;
		while (line[j] != 32 && line[j])
			j++;
		element_dir(element, line, i);
		ft_strlcpy(element[i].id, line, j + 1);
		element[i].id = ft_strdup(element[i].id);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
}

int	init_elements(t_element *element, int fd)
{
	elements_arr(element, fd);
	if (parse_colors(element) != 0)
	{
		free_elements(element);
		write(2, "error with rgb numbers\n", 23);
		return (1);
	}
	if (convert_rgb_hex(element) != 0)
	{
		free_elements(element);
		write(2, "error with rgb to hexx\n", 23);
		return (1);
	}
	if (parse_elements(element) != 0)
	{
		free_elements(element);
		return (1);
	}
	return (0);
}
