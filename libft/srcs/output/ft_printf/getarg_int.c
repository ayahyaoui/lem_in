/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getarg_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 11:26:58 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 16:07:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf/ft_printf.h"

void	ft_inthh(t_env *env, va_list ap)
{
	if (!(env->arg.c = (char)va_arg(ap, int)))
		env->nullarg = 1;
	ft_itoa_base_cust(env, env->tmpbuf, env->arg.c);
}

void	ft_inth(t_env *env, va_list ap)
{
	if (!(env->arg.i = (short int)va_arg(ap, int)))
		env->nullarg = 1;
	ft_itoa_base_cust(env, env->tmpbuf, env->arg.i);
}

void	ft_intl(t_env *env, va_list ap)
{
	if (!(env->arg.li = va_arg(ap, long int)))
		env->nullarg = 1;
	ft_ltoa_base_cust(env, env->tmpbuf, env->arg.li);
}

void	ft_intllz(t_env *env, va_list ap)
{
	if (!(env->arg.lli = va_arg(ap, long long int)))
		env->nullarg = 1;
	ft_lltoa_base_cust(env, env->tmpbuf, env->arg.lli);
}

void	ft_intj(t_env *env, va_list ap)
{
	if (!(env->arg.lli = va_arg(ap, intmax_t)))
		env->nullarg = 1;
	ft_lltoa_base_cust(env, env->tmpbuf, env->arg.lli);
}
