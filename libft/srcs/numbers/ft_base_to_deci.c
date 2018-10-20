/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_to_deci.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:13:34 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:22:29 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				base_len(unsigned int num, int base)
{
	int digits;

	digits = 0;
	while ((num = num / base) != 0)
		digits++;
	return (digits + 1);
}

unsigned int	ft_base_to_deci(unsigned int num, int base)
{
	int				len;
	unsigned int	value;
	int				denom;

	value = 0;
	len = base_len(num, base);
	while (len)
	{
		denom = ft_abs(ft_pow(10, len));
		value += (num / denom) * ft_pow(base, len);
		num -= ((num / denom) * denom);
		len--;
	}
	return (value += num);
}
