/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:06:00 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:21:00 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = len;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else while (i--)
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
	return (dst);
}
