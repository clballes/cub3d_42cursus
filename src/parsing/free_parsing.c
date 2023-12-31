/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:44:48 by clballes          #+#    #+#             */
/*   Updated: 2023/09/13 16:21:26 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*free_var(char *src, char *dest)
{
	char	*tmp;

	tmp = src;
	src = ft_strjoin(src, dest);
	free(tmp);
	return (src);
}

void	free_arr(char **copy_map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(copy_map[i]);
		i++;
	}
	free(copy_map);
}

void	free_elements(t_element *element)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		free(element[i].direction);
		free(element[i].id);
		i++;
	}
	free(element);
}

void	free_all(t_map *map, t_element *element, int i)
{
	free_elements(element);
	if (i == 0)
		free_arr(map->copy_map, map->rows);
	free_arr(map->map_arr, map->rows);
}
