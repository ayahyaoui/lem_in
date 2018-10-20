/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nblen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:42:09 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/30 16:45:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

int		ft_unblen(unsigned int num, int base)
{
	int len;

	len = 0;
	while ((num = num / base) != 0)
		len++;
	return (len + 1);
}

int		ft_llnblen(long long num, int base)
{
	int len;

	len = 0;
	while ((num = num / base) != 0)
		len++;
	return (len + 1);
}

int		ft_ullnblen(unsigned long long num, int base)
{
	int len;

	len = 0;
	while ((num = num / base) != 0)
		len++;
	return (len + 1);
}
