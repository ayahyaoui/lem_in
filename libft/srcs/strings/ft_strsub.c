/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:08:54 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:04:03 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int beg, size_t len)
{
	char			*str;
	unsigned int	i;

	str = NULL;
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
	return (str);
}
