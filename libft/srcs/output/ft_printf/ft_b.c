/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 19:46:44 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 14:12:01 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_b(t_env *env, char *format, va_list ap)
{
	(void)format;
	if (env->prec < 0)
		env->prec = 32;
	env->arg.ui = va_arg(ap, unsigned int);
	env->fill_field = env->field - env->prec - env->prec / 8;
	ft_addtobuf_field(env, ' ', env->fill_field);
	ft_printbit(env, env->arg.ui, env->prec);
	ft_strncpyi_buf(env, env->tmpbuf, &env->pindex, env->index);
}
