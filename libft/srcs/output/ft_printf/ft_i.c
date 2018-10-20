/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:43:33 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 14:48:19 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_i(t_env *env, char *format, va_list ap)
{
	static void (*ft_inttostr[7])(t_env *env, va_list ap) = {&ft_intnone,
		&ft_inth, &ft_inthh, &ft_intl, &ft_intllz, &ft_intllz, &ft_intj};

	(void)format;
	ft_inttostr[env->mod](env, ap);
	ft_apply_specs_int(env);
	ft_strncpyi_buf(env, env->tmpbuf, &env->pindex, env->index);
	if (env->fill_field > env->fill_prec)
		ft_addtobuf_field(env, ' ', env->fill_field);
	else if (env->flags & 1 << MINUS)
		ft_addtobuf_prec(env, ' ', env->fill_prec);
}
