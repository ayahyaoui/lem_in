/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnbci.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:12:02 by emuckens          #+#    #+#             */
/*   Updated: 2017/12/22 11:42:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnbci(char const *s, char c, int i)
{
	int count;

	count = 0;
	if (!s || !c)
		return (-1);
	while (*(s + i))
	{
		if (*(s + i) == c)
			++count;
		i++;
	}
	return (count);
}
