/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_inttab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:25:55 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 22:26:04 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_inttab(int *tab, int len, char c)
{
	int i;

	i = -1;
	if (!tab || len < 0)
		return ;
	while (++i < len)
		ft_printf("%d%c", tab[i], i == len - 1 ? '\n': c);
}
