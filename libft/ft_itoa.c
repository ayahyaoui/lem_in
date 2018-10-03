/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 20:21:37 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 04:03:49 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_base(int nb, int b)
{
	int		res;

	res = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
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

static char	*ft_itoo(long nb)
{
	char	*str;
	int		i;
	int		t;

	t = ft_len_base(nb, 10);
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (t + 1))))
		return (0x0);
	str[0] = '0';
	str[t] = '\0';
	if (nb < 0)
	{
		nb = nb * -1;
		i = 1;
		str[0] = '-';
	}
	while (--t > 0)
	{
		str[t] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (str[0] != '-')
		str[0] = nb + '0';
	return (str);
}

char		*ft_itoa(int n)
{
	long	nb;

	nb = n;
	return (ft_itoo(nb));
}
