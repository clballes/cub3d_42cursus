#include "cub3d.h"


int main(int argc, char **argv)
{
    if (argc > 2 || argc == 1)
        write(2, "just one .cub argument!\n", 24);
    else
    {
        if (init_parse(argv) != 0) //funcion q llama a otras para parsing mapa
            return (1); //parsing error encounter
    
    }
    return (0);
}