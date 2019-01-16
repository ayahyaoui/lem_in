/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:14:58 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 18:30:09 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** returns trueif string is only digits, with or without '-' as first char
*/

int			ft_isnumber(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != '-') || ((str[i] == '-') && i))
			return (FALSE);
		++i;
	}
	return (TRUE);
}
