/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:59:43 by clballes          #+#    #+#             */
/*   Updated: 2023/07/24 19:59:44 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_exten(char **argv)
{
	char	*str;
	char	*new_str;
	int		i;

	i = 0;
	str = "cub";
	while (argv[1][i])
	{
		if (argv[1][i] == '.')
		{
			new_str = argv[1] + i + 1;
			if (ft_strncmp(new_str, str, 4) == 0)
				return (0);
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	open_map(char **argv) //hacemos open del map y guardamos en estructura el texto
{
	int			fd;
	t_element	*element;
	t_map		*map;

	map = malloc(sizeof(t_map));
	element = malloc(6 * sizeof(t_element)); //create malloc del free
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free(element);
		write(2, "error opening map!\n", 19);
		return (1);
	}
	if (elements_arr(element, fd) != 0) //put elements text, in the array
	{
		write(2, "error with text parsing\n", 24);
		return (1);
	}
	if (init_map(map, fd) != 0)
	{
		write(2, "error creating the map\n", 23);
		return (1);
	}
	return (0);
}

int	init_parse(char **argv)
{
	if (cub_exten(argv) != 0)
	{
		write(2, "not .cub extension!\n", 21);
		return (1);
	}
	if (open_map(argv) != 0)
	{
	// write(2, "error with text parsing\n", 24);
		return (1);
	}
	return (0);
}
