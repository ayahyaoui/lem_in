/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:27:39 by emuckens          #+#    #+#             */
/*   Updated: 2018/06/14 22:21:05 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_nblen(n, 10);
	if (n < 0)
		++len;
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len-- && n / 10)
	{
		str[len] = (char)(ft_abs(n % 10) + '0');
		n /= 10;
	}
	str[len] = (char)((n > 0 ? n % 10 : -n % 10) + '0');
	if (n < 0)
		str[0] = '-';
	return (str);
}
