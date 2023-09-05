/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:34:37 by clballes          #+#    #+#             */
/*   Updated: 2023/09/05 19:50:33 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptrsrc;
	unsigned char	*ptrdst;

	ptrsrc = (unsigned char *) src;
	ptrdst = (unsigned char *) dst;
	i = 0;
	if (!ptrsrc && !ptrdst)
		return (0);
	while (i < n)
	{
		ptrdst[i] = ptrsrc[i];
		i++;
	}
	return (dst);
}
