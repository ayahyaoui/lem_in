/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_beyond_limiti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 19:31:32 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/10 19:33:58 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

int				ft_beyond_limiti(char *str)
{
	long	num;
	int		len;
	int		i;

	len = ft_strlen(str);
	num = 0;
	i = str[0] == '-' ? -1 : 1;
	while (--len >= 0 && str[len] != '-')
	{
		num += i * (str[len] - '0');
		if (num > INT_MAX)
			return (1);
		else if (num < INT_MIN)
			return (-1);
		i *= 10;
	}
	return (0);
}
