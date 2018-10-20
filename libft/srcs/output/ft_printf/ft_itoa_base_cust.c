/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_cust.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:40:35 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 14:33:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <limits.h>

static void	ft_mng_nullarg(t_env *env, int *num)
{
	env->neg = 1;
	*num *= -1;
}

void		ft_itoa_base_cust(t_env *env, unsigned char *str, int num)
{
	unsigned char	*tab;
	int				len;

	tab = (unsigned char *)"0123456789abcdef";
	if (num < 0)
		ft_mng_nullarg(env, &num);
	len = ftp_nblen(num, env->base);
	(str)[len] = '\0';
	if (env->arg.i == -2147483648)
	{
		ft_strncpyi_tmp(env, (unsigned char *)"2147483648", &env->index, 10);
		env->prec -= 11;
		env->neg = 1;
		return ;
	}
	env->index += len;
	while (len--)
		if (num % env->base >= 0)
		{
			(str)[len] = tab[(unsigned long long)num % env->base];
			num /= env->base;
		}
}
