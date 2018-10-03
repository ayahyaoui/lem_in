/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 17:53:22 by anyahyao          #+#    #+#             */
/*   Updated: 2018/03/09 21:30:19 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_remp_tab(char *str, int maj)
{
	int i;

	i = -1;
	while (++i < 10)
		str[i] = i + '0';
	i = -1;
	while (++i < 6)
		str[10 + i] = i + 'A' + (32 * maj);
	str[16] = '\0';
}

static void		ft_remp_res(char *res, char *str, long nb, int b)
{
	if (nb > 0)
	{
		res[0] = str[nb % b];
		ft_remp_res(&res[1], str, nb / b, b);
	}
}

char			*ft_itoa_base(long long nb, int base)
{
	long	n;
	size_t	len;
	char	*res;
	char	*tab;
	int		maj;

	maj = 1;
	n = nb;
	if (base == 10 || nb == 0)
		return (ft_itoa(nb));
	if (base < 2 || base > 16)
		return (0);
	if (n < 0)
		n *= -1;
	len = ft_lennbr_base(n, (size_t)base);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (0x0);
	if (!(tab = (char *)malloc(sizeof(char) * (17))))
		return (0x0);
	ft_remp_tab(tab, maj);
	res[len] = '\0';
	ft_remp_res(res, tab, n, base);
	ft_strrev(res);
	return (res);
}
