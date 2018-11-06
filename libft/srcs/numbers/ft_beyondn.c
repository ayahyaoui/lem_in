/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_beyondn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 19:31:32 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 17:28:29 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_beyondn(char *str, int n)
{
	long	num;
	int		len;
	int		coef;
	int		i;

	len = ft_strlen(str);
	num = 0;
	coef = (str[0] == '-' ? -1 : 1);
	i = (str[0] == '-' ? 1 : 0);
	while (i < len)
	{
		num += (str[i] - '0');
		if (num * coef > n)
			return (1);
		else if (num * coef < -n)
			return (-1);
		num *= 10;
		++i;
	}
	return (0);
}
