/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:17:37 by albagarc          #+#    #+#             */
/*   Updated: 2023/09/05 19:17:40 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rgb_decimal(t_element *element, int idx)
{
	element[idx].color = (element[idx].r << 16)
		+ (element[idx].g << 8) + element[idx].b;
}

void	extract_int(char *direction, t_element *element, int idx, int start)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = -1;
	j = 0;
	while (++i <= (int)ft_strlen(direction))
	{
		if (direction[i] == ',' || direction[i] == '\0')
		{
			len = i - start;
			str = ft_substr(direction, start, len);
			if (j == 0)
				element[idx].r = ft_atoi(str);
			else if (j == 1)
				element[idx].g = ft_atoi(str);
			else if (j == 2)
				element[idx].b = ft_atoi(str);
			free(str);
			start = i + 1;
			j++;
		}
	}
	rgb_decimal(element, idx);
}

int	convert_rgb_hex(t_element *element)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < 6)
	{
		if (ft_strncmp(element[i].id, "F", 2) == 0)
			extract_int(element[i].direction, element, 0, start);
		if (ft_strncmp(element[i].id, "C", 2) == 0)
			extract_int(element[i].direction, element, 1, start);
		i++;
	}
	return (0);
}
