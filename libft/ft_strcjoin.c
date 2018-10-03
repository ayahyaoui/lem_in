/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 22:50:42 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/19 22:56:32 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(char const *s1, char const *s2, char c)
{
	int		l;
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (0x0);
	l = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = (char *)malloc(sizeof(char) * (l + 2))))
		return (0x0);
	while (s1[++i])
		res[i] = s1[i];
	res[i] = c;
	while (s2[++j])
		res[i + j + 1] = s2[j];
	res[i + j + 1] = '\0';
	return (res);
}
