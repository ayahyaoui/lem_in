/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 21:31:18 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/18 18:08:05 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = -1;
	if (!s || !f)
		return (0x0);
	if ((!(str = ft_strdup(s))))
		return (0x0);
	while (s[++i])
		str[i] = f(i, (char)s[i]);
	return (str);
}
