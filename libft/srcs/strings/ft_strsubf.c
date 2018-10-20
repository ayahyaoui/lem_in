/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:08:54 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:04:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsubf(char const *s, unsigned int beg, size_t len, char *to_free)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	if (!(str = (char *)malloc(len + 1)))
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[i] = s[i + beg];
		i++;
	}
	ft_strdel(&to_free);
	return (str);
}
