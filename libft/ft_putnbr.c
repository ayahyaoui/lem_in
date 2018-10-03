/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 21:23:50 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/16 19:10:53 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbrec(long n)
{
	if (n / 10)
		ft_putnbrec(n / 10);
	ft_putchar((char)(n % 10) + '0');
}

void		ft_putnbr(int n)
{
	long nb;

	nb = n;
	if (n < 0)
	{
		write(1, "-", 1);
		nb = -1 * nb;
	}
	ft_putnbrec(nb);
}
