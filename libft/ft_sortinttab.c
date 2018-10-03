/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortinttab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 00:36:54 by anyahyao          #+#    #+#             */
/*   Updated: 2018/03/31 22:29:30 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_mintab(int *tab, int deb, int fin)
{
	int		min;
	int		res;

	res = deb;
	min = tab[deb];
	deb--;
	while (++deb < fin)
		if (tab[deb] < min)
		{
			min = tab[deb];
			res = deb;
		}
	return (res);
}

int			ft_sortinttab(int *tab, int s)
{
	int		i;
	int		j;
	int		b;

	if (!tab || s < 1)
		return (-1);
	i = 0;
	j = 0;
	while (i < s)
	{
		b = ft_mintab(tab, i, s);
		ft_swap(&tab[i], &tab[b]);
		i++;
	}
	return (1);
}
