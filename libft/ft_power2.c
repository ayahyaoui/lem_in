/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 17:00:22 by anyahyao          #+#    #+#             */
/*   Updated: 2018/03/16 22:11:20 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_power2(unsigned int val)
{
	unsigned long long res;

	res = 1;
	if (val > 128)
		return (0);
	if (val == 31)
		return (2147483648);
	while (val > 0)
	{
		res *= 2;
		val--;
	}
	return (res);
}
