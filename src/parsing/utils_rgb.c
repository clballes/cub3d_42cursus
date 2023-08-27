
#include "cub3d.h"

int hexCharToInt(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return 10 + (c - 'A');
	else if (c >= 'a' && c <= 'f')
		return 10 + (c - 'a');
	else
		return -1; // Invalid character
}

void	hexStringToDecimal(const char *hexString, t_element *element, int idx)
{
    int result;
	int digit;
 
	digit = 0;
	result = 0;
    if (hexString[0] == '0' && (hexString[1] == 'x' || hexString[1] == 'X'))
        hexString += 2;
    // Calculate the decimal value
    while (*hexString != '\0')
	{
        digit = hexCharToInt(*hexString);
        result = (result * 16) + digit;
        hexString++;
    }
	element[idx].color = result;
	free(element[idx].hexa);
}

void conver_hexa(t_element *element, int idx)
{
	char *hexa;

	hexa = malloc(sizeof(char *) * 8);
	element[idx].hexa = hexa;
    char hex_digits[] = "0123456789ABCDEF";
    
    element[idx].hexa[0] = '0';
    element[idx].hexa[1] = 'x';
    element[idx].hexa[2] = hex_digits[(element[idx].r >> 4) & 0x0F];
    element[idx].hexa[3] = hex_digits[element[idx].r & 0x0F];
    element[idx].hexa[4] = hex_digits[(element[idx].g >> 4) & 0x0F];
    element[idx].hexa[5] = hex_digits[element[idx].g & 0x0F];
    element[idx].hexa[6] = hex_digits[(element[idx].b >> 4) & 0x0F];
    element[idx].hexa[7] = hex_digits[element[idx].b & 0x0F];
    element[idx].hexa[8] = '\0';
	hexStringToDecimal(element[idx].hexa, element, idx);
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
	conver_hexa(element, idx);
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