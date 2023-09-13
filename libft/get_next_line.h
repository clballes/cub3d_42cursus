/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:40:50 by clballes          #+#    #+#             */
/*   Updated: 2023/09/13 16:15:24 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_strchr_get(char *s, int c);
char	*get_next_line(int fd);
char	*ft_protect(char *s1);
#endif
