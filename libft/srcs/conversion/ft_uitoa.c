/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:27:39 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:01:22 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*str;

	len = ft_nblen(n, 10);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len-- && n / 10)
	{
		str[len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	str[len--] = (n > 0 ? n % 10 : -(n % 10)) + '0';
	str[len] = (n > 0 ? n / 10 : -(n / 10)) + '0';
	return (str);
}
