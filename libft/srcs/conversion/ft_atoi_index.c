/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:32:06 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 16:04:41 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi_index(unsigned char *str, int *count)
{
	int neg;
	int value;
	int index;

	value = 0;
	index = 0;
	neg = (*str == '-') ? 1 : 0;
	if (neg || str[index] == '+' || str[index] == '-')
		++index;
	while (str[index] <= '9' && str[index] >= '0')
	{
		value = (str[index] - '0') + 10 * value;
		++index;
	}
	while (str[index] == ' ')
		++index;
	*count = index;
	return (neg ? -value : value);
}
