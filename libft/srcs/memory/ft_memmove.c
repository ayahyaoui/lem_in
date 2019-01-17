/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:06:00 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 22:41:13 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = len;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		while (i--)
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
	return (dst);
}
