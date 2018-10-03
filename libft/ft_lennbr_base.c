/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lennbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 19:13:42 by anyahyao          #+#    #+#             */
/*   Updated: 2018/03/16 20:21:58 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_lennbr_base(long long nb, int b)
{
	size_t	res;

	res = 0;
	if (b < 2 || b > 16)
		return (0);
	if (nb == 0)
		return (1);
	if (nb < 0 && b == 10)
	{
		nb *= -1;
		res++;
	}
	while (nb)
	{
		nb = nb / b;
		res++;
	}
	return (res);
}

size_t		ft_lenbase(long long nb, size_t b)
{
	size_t	res;

	res = 1;
	if (b < 2 || b > 16)
		return (0);
	if (nb < 0)
	{
		nb *= -1;
		res++;
	}
	while ((nb = (nb / b)) > 0)
		res++;
	return (res);
}

size_t		ft_lenbase2(long long nb, size_t b, int size)
{
	size_t	res;
	int		dec;

	res = 1;
	if (b < 2 || b > 16)
		return (0);
	if (nb < 0)
	{
		dec = log2_simp(b);
		res = size * 8 / dec;
		if ((size * 8) % dec)
			res++;
	}
	else
		while ((nb = (nb / b)) > 0)
			res++;
	return (res);
}
