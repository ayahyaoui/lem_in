/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:36:22 by emuckens          #+#    #+#             */
/*   Updated: 2017/11/22 19:25:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_special(char c)
{
	return (c == '\f' || c == '\v' || c == '\r' || c == '\n'
			|| c == '\t' || c == ' ');
}

int			ft_atoi(const char *nptr)
{
	int neg;
	int value;
	
	value = 0;
	while (is_special(*nptr))
		nptr++;
	neg = (*nptr == '-') ? 1 : 0;
	if (neg || *nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr <= '9' && *nptr >= '0')
		value = (*nptr++ - '0') + 10 * value;
	return (neg ? -value : value);

}
