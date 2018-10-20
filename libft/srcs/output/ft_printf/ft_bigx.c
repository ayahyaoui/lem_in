/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:46:45 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 16:22:38 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_bigx(t_env *env, char *format, va_list ap)
{
	static void (*ft_unstostr[7])(t_env *env, va_list ap) = {&ft_unsnone,
		&ft_unsh, &ft_unshh, &ft_unsl, &ft_unsll, &ft_unsz, &ft_unsj};

	(void)format;
	env->base = 16;
	ft_unstostr[env->mod](env, ap);
	if (env->nullarg && env->prec != -100)
	{
		env->tmpbuf[0] = 0;
		env->index = 0;
	}
	ft_apply_specs_hex(env);
	ft_strcapitalize(env->tmpbuf);
	ft_strncpyi_buf(env, env->tmpbuf, &env->pindex, env->index);
	if (env->fill_field > env->fill_prec)
		ft_addtobuf_field(env, ' ', env->fill_field);
	else if (env->flags & 1 << MINUS)
		ft_addtobuf_prec(env, ' ', env->fill_prec);
}
