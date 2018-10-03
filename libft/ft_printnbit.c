/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:53:17 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 01:24:21 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printnbit(int val, int max)
{
	int		i;
	int		power;
	char	s[32];

	i = 0;
	if (max < 1 || max > 32)
		return (-1);
	power = ft_power2((unsigned int)max - 1);
	while (i < max)
	{
		if (val & power)
			s[i] = '1';
		else
			s[i] = '0';
		i++;
		val = val << 1;
	}
	s[i] = '\0';
	write(1, s, max);
	return (1);
}
