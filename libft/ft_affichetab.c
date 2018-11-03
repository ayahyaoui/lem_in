/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affichetab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 00:55:34 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/02 22:27:27 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_affichetab(int *tab, int s, char c)
{
	int		i;

	if (!tab || s < 1)
		return (-1);
	i = -1;
	while (++i < s - 1)
	{
		ft_putnbr(tab[i]);
		write(1, &c, 1);
	}
	if (i < s)
		ft_putnbr(tab[i]);
	write(1, "\n", 1);
	return (1);
}
