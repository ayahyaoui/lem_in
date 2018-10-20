/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:50:28 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 14:49:21 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

static void	ft_mng_nullarg(t_env *env, int *n)
{
	if (env->prec == -100)
		ft_strncpyi_tmp(env, (unsigned char *)"(null)", n, 6);
	else
		ft_strncpyi_tmp(env, (unsigned char *)"(null)", n, env->prec);
	env->field -= *n;
}

void		ft_s(t_env *env, char *format, va_list ap)
{
	env->str = NULL;
	if (env->mod == L)
	{
		ft_bigs(env, format, ap);
		return ;
	}
	env->arg.s = va_arg(ap, unsigned char *);
	env->prec = env->prec == -99 ? 0 : env->prec;
	if (!env->arg.s || env->arg.s == NULL)
		ft_mng_nullarg(env, &env->index);
	else if (env->prec > 0)
		ft_strncpyi_tmp(env, env->arg.s, &env->index, env->prec);
	else if (env->prec == -100)
		env->str = env->arg.s;
	ft_apply_specs_str(env);
	if (env->str)
		ft_strcpyi_buf(env, (unsigned char *)env->str, &env->pindex);
	else
		ft_strncpyi_buf(
			env, (unsigned char *)env->tmpbuf, &env->pindex, env->index);
	ft_addtobuf_field(env, ' ', env->fill_field);
}
