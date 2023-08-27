/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:59:43 by clballes          #+#    #+#             */
/*   Updated: 2023/07/31 13:42:55 by albagarc         ###   ########.fr       */
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
			{
				write(2, "not .cub extension!\n", 21);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	init_parse(char **argv, t_map *map, t_all *all)
{
	int			fd;
	t_element	*element;
	element = ft_calloc(6, sizeof(t_element));
	all->element = element;
	if (cub_exten(argv) != 0)
	{
		free(element);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free(element);
		write(2, "error opening map!\n", 19);
		return (1);
	}
	if (init_elements(element, fd) != 0)
		return (1);
	if (init_map(element, fd, map) != 0)
		return (1);
	return (0);
}
