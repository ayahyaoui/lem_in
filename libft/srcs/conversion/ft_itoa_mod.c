/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 19:57:21 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/26 16:39:37 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void		ft_itoa_mod(char str[], int num)
{
	unsigned char	*tab;
	int				len;
	int				neg;

	neg = 0;
	tab = (unsigned char *)"0123456789";
	if (num == INT_MIN)
		ft_strcpy((char *)str, "-2147483648");
	else if (num < 0 && (neg = 1))
	{
		str[0] = '-';
		num *= -1;
	}
	len = ft_nblen(num, 10) + neg;
	(str)[len] = '\0';
	while (len--)
		if (num % 10 >= 0)
		{
			(str)[len] = tab[(unsigned long long)num % 10];
			num /= 10;
		}
}
