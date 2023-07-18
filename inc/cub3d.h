

#ifndef CUB_3D_H
# define CUB_3D_H

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

typedef struct s_element //esto sera un array que guardaremos la info de los elementos de texto del mapa
{
    char *id; //identifier NO, SO, WE, EA, F, C
    char *direction; // direction or colors
    // t_map *map; //puntero a estructura del mapa con los numeros ltras, esto nose
}           t_element;

typedef struct s_map
{
    // char **map; //nose si es mejor todo en array o lista
    t_element *element; //puntero a estructura array del texto
} t_map;

//parsing map
int     init_parse(char **argv);
int    elements_arr(t_element *element, int fd);
int ft_digit(char *str);

#endif