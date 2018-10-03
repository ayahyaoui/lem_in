/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:15:10 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/18 19:31:48 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *s)
{
	int i;
	int j;
	int t;

	i = 0;
	t = ft_strlen(s);
	if (t == 0)
		return ((char *)str);
	if ((int)ft_strlen(str) >= t)
		while (str[i + t - 1])
		{
			j = 0;
			if (str[i] == s[0])
			{
				while (s[j] && str[i + j] == s[j])
					j++;
				if (j == t)
					return (&((char *)str)[i]);
			}
			i++;
		}
	return (0);
}
