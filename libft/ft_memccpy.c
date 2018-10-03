/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 23:19:09 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/14 15:44:50 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[0] = ((unsigned char *)src)[0];
		dest++;
		if (((unsigned char *)src)[0] == (unsigned char)c)
			return (dest);
		src++;
		i++;
	}
	return (0x0);
}
