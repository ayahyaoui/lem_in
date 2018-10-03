/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:24:34 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/18 18:04:37 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		t;
	char	*res;

	t = ft_strlen(str);
	if (!str || !(res = (char*)malloc(sizeof(char) * (t + 1))))
		return (0x0);
	res[t] = '\0';
	while (--t > -1)
		res[t] = str[t];
	return (res);
}
