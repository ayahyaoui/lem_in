/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:30:06 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 13:37:15 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf/ft_printf.h"

void	ft_printbit(t_env *env, unsigned int n, int size)
{
	unsigned	mask;
	unsigned	i;

	mask = ~(~0U >> 1);
	i = 0;
	env->j = 32;
	while (mask > 0 && n)
	{
		if (env->j <= size)
		{
			if (env->index != 0 && i != 0 && i % 4 == 0)
				env->tmpbuf[env->index++] = ' ';
			env->tmpbuf[env->index] = ((n & mask) ? '1' : '0');
			++env->index;
		}
		--env->j;
		mask >>= 1;
		++i;
	}
}
