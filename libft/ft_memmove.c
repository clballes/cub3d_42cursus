/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:59:55 by clballes          #+#    #+#             */
/*   Updated: 2023/09/05 19:25:44 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptrsrc;
	unsigned char	*ptrdst;

	ptrsrc = (unsigned char *) src;
	ptrdst = (unsigned char *) dst;
	if (ptrdst == ptrsrc || len == 0)
		return (dst);
	if (ptrdst > ptrsrc)
	{
		while (len > 0)
		{
			ptrdst[len - 1] = ptrsrc[len - 1];
			len--;
		}
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
