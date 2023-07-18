#include "cub3d.h"

int ft_digit(char *str)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (str[i] >= 48 && str[i] <= 57)
            i++;
        else
            return (1);
    }
    return (0);
}