/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:09:40 by clballes          #+#    #+#             */
/*   Updated: 2023/09/13 16:23:46 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static char	*ft_fill_storage(char *storage, int fd)
{
	char	*buffer;
	int		nbytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	nbytes = 1;
	while (nbytes > 0 && !ft_strchr_get(buffer, '\n'))
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes > 0)
		{
			buffer[nbytes] = '\0';
			storage = ft_strjoin_get(storage, buffer);
		}
	}
	free (buffer);
	if (nbytes == -1)
		return (NULL);
	return (storage);
}

char	*ft_get_a_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	if (!storage[0])
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (storage[i] == '\0')
		line = malloc ((i + 1) * (sizeof(char)));
	else
		line = malloc ((i + 2) * (sizeof(char)));
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] != '\n' && storage[i] != '\0')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n' || storage[i] == '\0')
		line [i] = '\0';
	return (line);
}

char	*ft_save_line(char *storage)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	if (storage[i] == '\0')
	{
		free (storage);
		return (NULL);
	}
	i++;
	str = malloc((ft_strlen(storage) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (storage[i] != '\0')
		str[j++] = storage[i++];
	str[j] = '\0';
	free (storage);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;
	int			c;
	char		*a;

	c = 0;
	a = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage[fd] || (storage[fd] && !ft_strchr_get(storage[fd], '\n')))
	{
		a = ft_fill_storage(storage[fd], fd);
		if (!a)
		{
			free(storage[fd]);
			return (NULL);
		}
		storage[fd] = a;
	}
	if (!storage[fd])
		return (NULL);
	line = ft_get_a_line(storage[fd]);
	storage[fd] = ft_save_line(storage[fd]);
	return (line);
}
