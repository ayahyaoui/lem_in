/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:14:14 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/18 19:35:02 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *str, size_t n)
{
	size_t i;

	i = 0;
	while (str[i] && i < n)
	{
		dst[i] = ((char *)str)[i];
		i++;
	}
	i--;
	while (++i < n)
		dst[i] = '\0';
	return (dst);
}
