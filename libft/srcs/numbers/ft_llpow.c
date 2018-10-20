/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llpow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:58:20 by emuckens          #+#    #+#             */
/*   Updated: 2018/01/24 12:20:27 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_llpow(long long n, int pow)
{
	long long result;

	result = 1;
	if (pow <= 0)
		return (pow ? 0 : 1);
	++pow;
	while (--pow >= 1)
		result *= n;
	return (result);
}
