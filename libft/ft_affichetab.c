/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affichetab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 00:55:34 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 02:55:36 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_affichetab(int *tab, int s, char c)
{
	int		i;

	if (!tab || s < 1)
		return (-1);
	i = -1;
	while (++i < s)
	{
		ft_putnbr(tab[i]);
		write(1, &c, 1);
	}
	write(1, "\n", 1);
	return (1);
}
