/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:34:39 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:29:48 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	max;
	size_t	len_dst;
	size_t	len_src;
	char	*ptr;

	ptr = (char *)(unsigned long)src;
	len_src = ft_strlen(ptr);
	len_dst = ft_strlen(dst);
	max = ft_abs((int)(size - len_dst - 1));
	while (*dst)
		dst++;
	if (len_dst < size)
		while (*src && max--)
			*dst++ = *src++;
	*dst = '\0';
	return (size < len_dst ? len_src + size : len_dst + len_src);
}
