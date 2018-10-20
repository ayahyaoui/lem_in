/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:42:30 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 14:49:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_p(t_env *env, char *format, va_list ap)
{
	static void (*ft_ptrtostr[7])(t_env *env, va_list ap) = {&ft_unsl,
		&ft_unsnone, &ft_unsnone, &ft_unsl, &ft_unsll, &ft_unsz, &ft_unsj};

	(void)format;
	env->base = 16;
	ft_ptrtostr[env->mod](env, ap);
	ft_apply_specs_ptr(env);
	ft_strncpyi_buf(env, env->tmpbuf, &env->pindex, env->index);
	if (env->fill_field > env->fill_prec)
		ft_addtobuf_field(env, ' ', env->fill_field);
	else if (env->flags & 1 << MINUS)
		ft_addtobuf_prec(env, ' ', env->fill_prec);
}
