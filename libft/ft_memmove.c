/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:45:11 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/14 21:59:09 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		p;

	if (dest > src)
		while (n--)
			((unsigned char*)dest)[n] = ((unsigned char *)src)[n];
	else
	{
		p = 0;
		while (p < n)
		{
			((unsigned char*)dest)[p] = ((unsigned char *)src)[p];
			p++;
		}
	}
	return (dest);
}
