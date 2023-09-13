/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:39:37 by clballes          #+#    #+#             */
/*   Updated: 2023/09/13 16:22:36 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_is_space(char c)
{
	if (c == 32 || c == '\f' || c == '\n' || c == '\r' \
		|| c == '\t' || c == '\v')
		return (1);
	return (0);
}

char	*ft_trim_sp(char const *s1)
{
	char	*trim;
	int		i;
	int		j;

	if (s1 == 0)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_is_space(s1[i]))
		i++;
	while (s1[i] && ft_is_space(s1[j - 1]))
		j--;
	trim = ft_substr(s1, i, j - i);
	return (trim);
}

void	element_dir(t_element *element, char *line, int i, int j)
{
	int	size;

	size = 3;
	if (line[j] == 'F' || line[j] == 'C')
		size = 2;
	element[i].direction = line + j + size;
	element[i].direction = ft_trim_sp(element[i].direction);
}

void	element_id(t_element *element, int i, char *line, int j)
{
	int	len;

	len = 3;
	if (line[j] == 'F' || line[j] == 'C')
		len = 2;
	element[i].id = ft_calloc(len, sizeof(char *));
	ft_strlcpy(element[i].id, line + j, len);
}

int	elements_arr(t_element *element, int fd)
{
	int		i;
	int		j;
	char	*line;

	i = -1;
	while (++i < 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
		while (ft_strlen(line) == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		j = 0;
		while (ft_is_space(line[j]) == 1)
			j++;
		element_id(element, i, line, j);
		element_dir(element, line, i, j);
		free(line);
	}
	return (0);
}
