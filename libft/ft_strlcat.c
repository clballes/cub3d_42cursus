/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:23:52 by clballes          #+#    #+#             */
/*   Updated: 2023/09/05 19:50:46 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen (dst);
	j = ft_strlen(src);
	k = 0;
	if (dstsize == 0)
		return (j);
	if (dstsize <= i)
		return (dstsize + j);
	dstsize -= i;
	while (--dstsize && src[k])
	{
		dst[i + k] = src[k];
		++k;
	}
	dst[i + k] = '\0';
	return (i + j);
}
