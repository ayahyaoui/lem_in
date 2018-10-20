/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:49:28 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:31:22 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	ptr = (char *)(unsigned long)haystack;
	if (ft_strequ(needle, ""))
	{
		if (ft_strequ(haystack, ""))
			return (ptr + ft_strlen(ptr));
		return (ptr);
	}
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			j++;
			if (!needle[j])
				return (ptr + i);
		}
		i++;
	}
	return (0);
}
