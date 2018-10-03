/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:47:32 by anyahyao          #+#    #+#             */
/*   Updated: 2018/08/02 02:35:15 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**
*/

#define MAX_INT 2147483647

int		ft_isinteger(char *str)
{
	int			i;
	long long	nb;

	i = -1;
	if (*str == '-' || *str == '+')
		i++;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	nb = ft_atol(str);
	if (i > 10 || nb > MAX_INT)
		return (0);
	return (1);
}
