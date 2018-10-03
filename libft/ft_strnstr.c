/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:14:38 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/19 20:47:05 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *s, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = (int)ft_strlen(s);
	if (len == 0)
		return ((char *)str);
	if (n == 0)
		return (0x0);
	if (ft_strlen(str) >= len && len <= n)
		while (str[i + len - 1] && i <= n - len)
		{
			j = 0;
			if (str[i] == s[0])
			{
				while (s[j] && str[i + j] == s[j])
					j++;
				if (j == len)
					return (&((char*)str)[i]);
			}
			i++;
		}
	return (0);
}
