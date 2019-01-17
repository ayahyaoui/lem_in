/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_beyondn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:39:28 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 22:39:31 by emuckens         ###   ########.fr       */
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
