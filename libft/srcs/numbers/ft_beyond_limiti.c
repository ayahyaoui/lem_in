/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_beyond_limiti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 19:31:32 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 04:06:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

int				ft_beyond_limiti(char *str)
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
		if (num * coef > INT_MAX)
			return (1);
		else if (num * coef < INT_MIN)
			return (-1);
		num *= 10;
		++i;
	}
	return (0);
}
