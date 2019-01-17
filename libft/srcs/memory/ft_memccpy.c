/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:59:39 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 22:41:58 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** weird double cast to silent drop const qualifier error - use with caution
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*src_cpy;
	unsigned char		*ptr_dst;

	src_cpy = (const unsigned char *)src;
	ptr_dst = (unsigned char *)(unsigned long)dst;
	if (!(char *)ft_memchr(src_cpy, (unsigned char)c, n))
	{
		while (n--)
			ft_memcpy(ptr_dst++, src_cpy++, 1);
		return (NULL);
	}
	while (*src_cpy != (unsigned char)c && --n)
		ft_memcpy(ptr_dst++, src_cpy++, 1);
	ft_memcpy(ptr_dst, src_cpy, 1);
	return (n ? ptr_dst + 1 : NULL);
}
