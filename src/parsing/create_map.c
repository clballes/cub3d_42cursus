
#include "cub3d.h"

// int check_sp(t_map *map)
// {
//     int i;
//     int j;

//     i = 0;
//     while(map->map_arr[i])
//     {
//         j = 0;
//         while(map->map_arr[i][j])
//         {
//             if (map->map_arr[i][j] == 32)
//                 map->map_arr[i][j] = 'A';
//             j++;   
//         }
//         i++;
//     }
//     return (0);
// }

int check_walls(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(map->map_arr[i])
    {
        j = 0;
        while(map->map_arr[i][j])
        {
            while (map->map_arr[i][j] == 32)
            {
                if (map->map_arr[i][j]) = '1';
            }
            j++;   
        }
        i++;
    }
    return (0);
}

void	ft_arraymap(t_map *map)
{
    int i = 0;
	map->map_arr = ft_split(map->map_unid, '\n'); //free aqui
    // if (check_sp(map) != 0)
    //     write(2, "ERROR MAP NOT SURRENDEDD BY DEALT WITH SP\n", 43);
    if (check_walls(t_map *map) != 0)
        write(2, "ERROR MAP NOT SURRENDEDD BY WALLS\n", 33);
    
    while(i  < map->rows)
    {
        printf("%s\n", map->map_arr[i]);
        i++;
    }

}

char	*free_var(char *src, char *dest)
{
	char	*tmp;

	tmp = src;
	src = ft_strjoin(src, dest);
	free(tmp);
	return (src);
}

int init_map(t_map *map, int fd) //hacemos open del map y guardamos en estructura el mapa, que llamara otras funciones check errores
{
    char *line;
    // int len;
    int i;

    i = 0;
    map->map_unid = NULL;
    line = get_next_line(fd);
    while (line)
	{
        while (ft_strlen(line) == 0)
        {
            free(line);
            line = get_next_line(fd);
        }
		if (!map->map_unid)
			map->map_unid = ft_strdup(line);
		else
			map->map_unid = free_var(map->map_unid, line);
		map->map_unid = free_var(map->map_unid, "\n");
		free(line);
		line = get_next_line(fd);
		i++;
	}
    map->rows = i;
    ft_arraymap(map);

    // map->cols = len;
    return (0);
}

