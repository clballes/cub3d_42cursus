#include "cub3d.h"

void    free_element(t_element *element)
{
    int i;
    i = 0;
    while(i < 6)
    {
        free(element[i].direction);
        free(element[i].id);
        i++;
    }
    free(element);
}