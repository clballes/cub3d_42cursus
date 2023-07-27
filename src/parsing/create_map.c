/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clballes <clballes@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:59:05 by clballes          #+#    #+#             */
/*   Updated: 2023/07/24 19:59:06 by clballes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	max_x(t_map *map) //max x
{
	int i;
	int j;

	j = 0;
	i = 0;
	map->max_x = 0;
	while(map->map_arr[i])
	{
		while(map->map_arr[i][j])
			j++;
		if (map->max_x < j)
			map->max_x = j;
		j = 0;
		i++;
	}
}


int check_walls_row(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(map->map_arr[i])
    {
        j = 0;
        while(map->map_arr[i][j])
        {
            while (map->map_arr[i][j]) //check linea horizontal
            {
				if (map->map_arr[i][j] == 32 )
				{
					if (i == (map->rows - 1)) //i ens trobem un espai en la ulima row
					{
						while(map->map_arr[i - 1][j] == 32)
							i--;
						if (map->map_arr[i - 1][j] == '1')
						{
							i = map->rows - 1;
							j++;
						}
						else
							return (1);
					}
					else if (i == 0) //i ens trobem un espai en la primera
					{
						while(map->map_arr[i + 1][j] == 32)
							i++;
						if (map->map_arr[i + 1][j] == '1')
						{
							i = 0;
							j++;
						}
						else
							return (1);
					}
					j++;
				}
				else if (map->map_arr[i][j] == '1')
					j++;
				else
					return (1);
            }
        }
		if (i == map->rows - 1)
			break ;
        i = map->rows - 1; // per comprobar el final de leix horizontal
	}
    return (0);
}

// int check_walls_col(t_map *map)
// {
// 	// int i;
//     // int j;
// 	// int	len;

//     // j = 0;
// 	// len = 0;
//     // i = 0;
//     // while (map->map_arr[i])
//     // {
//     //     i = 0;
//     //     while (map->map_arr[i][j])
//     //     {
//     //         while (map->map_arr[i][j]) //check cols quan la i == 0
//     //         {
// 	// 			if (j == 0) //i ens trobem un espai en la ulima row
// 	// 			{
// 	// 				while (map->map_arr[i][j] == '0')
// 	// 					i++;
// 	// 				while (map->map_arr[i][j] == '1')
// 	// 				{
// 	// 					if (map->map_arr[i][j] == '0')
// 	// 					{
// 	// 						i = len; //i = columna 8
// 	// 						while (map->map_arr[i + 1][j] == '0')
// 	// 							i++;	//suma dos = i = 10
// 	// 						len = i - len;
// 	// 						// si la len es 1
// 	// 						while (j < len) //tornem a la posicio q estavem
// 	// 						{
// 	// 							map->map_arr[i--][j];
// 	// 							j++;
// 	// 						}
// 	// 						j = 0;
// 	// 						if (map->map_arr[i][j + 1] == '0')

// 	// 					}
// 	// 					i++;
// 	// 				}
// 	// 			}
// 	// 			else if (j == map->max_x - 1) //en strobem en la ultima col
// 	// 			{
// 	// 				while(map->map_arr[i][j - 1] == 32)
// 	// 					j--;
// 	// 				if (map->map_arr[i][j - 1] == '1')
// 	// 				{
// 	// 					i++;
// 	// 					j = map->max_x - 1;
// 	// 				}
// 	// 				else
// 	// 					return (1);
// 	// 			}
// 	// 			j++;
// 	// 		}
// 	// 		else if (map->map_arr[i][j] == '1')
// 	// 			j++;
// 	// 		else
// 	// 			return (1);
//     //         }
//     //     }
// 	// 	if (j == map->max_x - 1)
// 	// 		break ;
//     //     j = map->max_x - 1; // per comprobar el final de leix horizontal
// 	// }
//     // return (0);
// }


void	handle_sp(t_map *map) //put spaces to 0
{
	int i;
	int j;

	i = 0;
	while(map->map_arr[i])
	{
		j = 0;
		while(map->map_arr[i][j])
		{
			if (map->map_arr[i][j] == 32)
				map->map_arr[i][j] = '0';
			j++;
		}
		i++;
	}
	i = 0;
	while(map->map_arr[i])
	{
		printf("%s\n", map->map_arr[i]);
		i++;
	}
}

void	ft_arraymap(t_map *map)
{
    // int i = 0;
	map->map_arr = ft_split(map->map_unid, '\n'); //free aqui
	max_x(map); //check max x
    handle_sp(map);
	// check_walls_col(map);
	// if (check_walls_row(map) != 0)
    //     write(2, "ERROR MAP NOT SURRENDEDD BY WALLS\n", 33);
	// if (check_walls_col(map) != 0)
    //     write(2, "ERROR MAP NOT SURRENDEDD BY WALLS\n", 33);
    // if (check_sp(map) != 0)
    //     write(2, "ERROR MAP NOT SURRENDEDD BY DEALT WITH SP\n", 43);
    
    // while(i  < map->rows)
    // {
    //     printf("%s\n", map->map_arr[i]);
    //     i++;
    // }

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
    return (0);
}

