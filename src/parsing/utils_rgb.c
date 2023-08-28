#include "cub3d.h"

void rgb_decimal(t_element *element, int idx)
{
    element[idx].color = (element[idx].r << 16) + (element[idx].g << 8) + element[idx].b;
}

void	extract_int(char *direction, t_element *element, int idx)
{
	int		i;
	int		start;
	int		j;
	int		len;
	char 	*str;

	start = 0;
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
	int i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(element[i].id, "F", 2) == 0)
			extract_int(element[i].direction, element, 0);
		if (ft_strncmp(element[i].id, "C", 2) == 0)
			extract_int(element[i].direction, element, 1);
		i++;
	}
	return (0);
}