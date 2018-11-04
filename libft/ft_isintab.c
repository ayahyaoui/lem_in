/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:58:09 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/04 14:58:17 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isintab(int *tab, int len, int value)
{
	int i;

	if (!tab)
		return (-1);
	i = -1;
	while (++i < len)
		if (tab[i] == value)
			return (1);
	return (0);
}
