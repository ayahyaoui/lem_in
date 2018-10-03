/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logarithme2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 03:59:04 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/25 04:08:40 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	approximation de log 2
**	max est 31 envois 
** 
*/


unsigned int	ft_logarithme2(unsigned int nb)
{
	int		res;

	res = 0;
	if (nb == 0)
	{
		ft_putstr("Error log(0)\n");
		return (0);
	}
	while (ft_power2(res) < (unsigned long long)nb && res < 32)
		res ++;
	return (res);
}
