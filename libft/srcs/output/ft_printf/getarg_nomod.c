/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getarg_nomod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:53:57 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 16:16:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <stdarg.h>

void	ft_intnone(t_env *env, va_list ap)
{
	if (!(env->arg.i = (int)va_arg(ap, int)))
		env->nullarg = 1;
	ft_itoa_base_cust(env, env->tmpbuf, env->arg.i);
}

void	ft_unsnone(t_env *env, va_list ap)
{
	if (!(env->arg.ui = (unsigned int)va_arg(ap, int)))
		env->nullarg = 1;
	ft_uitoa_base_cust(env, env->tmpbuf, env->arg.ui);
}

void	ft_unsz(t_env *env, va_list ap)
{
	if (!(env->arg.ulli =
				(unsigned long long)va_arg(ap, unsigned long long int)))
		env->nullarg = 1;
	ft_ulltoa_base_cust(env, env->tmpbuf, env->arg.ulli);
}
