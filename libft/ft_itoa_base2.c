/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 23:04:23 by anyahyao          #+#    #+#             */
/*   Updated: 2018/03/16 22:15:49 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**		pour ce programme il faut que la base soit sous forme 2^n
**		avec n > 0 && n < 5 la reaction du programme
**		dans un autre cas n'est pas prevu
*/

int				log2_simp(int n)
{
	int		res;

	res = 0;
	if (n < 1)
		exit(0);
	while (n != 1)
	{
		n = n >> 1;
		res++;
	}
	return (res);
}

static	int		ispower2(int b)
{
	if (b < 1)
		return (0);
	while (b && (b & 1) == 0)
		b = b >> 1;
	if (b == 1)
		return (1);
	else
		return (0);
}

static	void	ft_remp_tab(char *str, int maj)
{
	int		i;

	i = -1;
	while (++i < 10)
		str[i] = i + '0';
	i = -1;
	while (++i < 6)
		str[10 + i] = i + 'a' - (32 * maj);
	str[16] = '\0';
}

char			*ft_itoa_base2(long long n, int base, int size, int maj)
{
	int		len;
	char	*res;
	char	*tab;
	int		dec;

	if (base < 2 || base > 16 || size <= 0 || size > 16)
		return (0);
	if (!ispower2(base))
		return (ft_itoa_base(n, base));
	dec = log2_simp(base);
	len = ft_lenbase2(n, (size_t)base, size);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (0x0);
	if (!(tab = (char *)malloc(sizeof(char) * (17))))
		return (0x0);
	ft_remp_tab(tab, maj);
	res[len] = '\0';
	while (len > 0)
	{
		res[len - 1] = tab[n & (base - 1)];
		len--;
		n = (n >> dec) & (ft_power2(size * 8 - dec) - 1);
		
	}
	free(tab);
	return (res);
}
