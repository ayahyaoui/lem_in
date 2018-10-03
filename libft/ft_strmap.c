/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 21:23:00 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 04:02:03 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;

	i = -1;
	if (!s || !f)
		return (0x0);
	if (!(str = ft_strdup(s)))
		return (0x0);
	while (s[++i])
		str[i] = f((char)s[i]);
	return (str);
}
