/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getarg_uns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 11:26:58 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 16:17:27 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf/ft_printf.h"

void	ft_unshh(t_env *env, va_list ap)
{
	if ((env->arg.uli = va_arg(ap, int)) == 0)
		env->nullarg = 1;
	env->arg.ui = (unsigned char)env->arg.uli;
	ft_uitoa_base_cust(env, env->tmpbuf, env->arg.ui);
}

void	ft_unsh(t_env *env, va_list ap)
{
	if ((env->arg.lli = va_arg(ap, int)) == 0)
		env->nullarg = 1;
	env->arg.ui = (unsigned short int)env->arg.lli;
	ft_uitoa_base_cust(env, env->tmpbuf, env->arg.ui);
}

void	ft_unsl(t_env *env, va_list ap)
{
	ft_unsj(env, ap);
}

void	ft_unsll(t_env *env, va_list ap)
{
	if (!(env->arg.ulli = va_arg(ap, unsigned long long int)))
		env->nullarg = 1;
	ft_ulltoa_base_cust(env, env->tmpbuf, env->arg.ulli);
}

void	ft_unsj(t_env *env, va_list ap)
{
	if (!(env->arg.ulli = (intmax_t)va_arg(ap, long int)))
		env->nullarg = 1;
	ft_ulltoa_base_cust(env, env->tmpbuf, env->arg.ulli);
}
