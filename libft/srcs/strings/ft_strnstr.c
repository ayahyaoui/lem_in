/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:34:01 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:33:51 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_compare(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;
	size_t	len_cpy;

	len_cpy = len;
	i = 0;
	ptr = (char *)(unsigned long)haystack;
	while (haystack[i] && len)
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (!len--)
				return (0);
			j++;
			if (!needle[j])
				return (ptr + i);
			else if (haystack[i + j] != needle[j])
				len = len_cpy - i;
		}
		i++;
		len--;
	}
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char *ptr;

	ptr = (char *)(unsigned long)haystack;
	if (ft_strequ(needle, ""))
	{
		if (ft_strequ(haystack, ""))
			return (ptr + ft_strlen(ptr));
		return (ptr);
	}
	return (ft_compare(ptr, (char *)(unsigned long)needle, len));
}
