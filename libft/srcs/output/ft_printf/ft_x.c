/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:46:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 16:22:09 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_x(t_env *env, char *format, va_list ap)
{
	static void (*ft_unstostr[7])(t_env *env, va_list ap) = {&ft_unsnone,
		&ft_unsh, &ft_unshh, &ft_unsl, &ft_unsll, &ft_unsz, &ft_unsj};

	(void)format;
	env->base = 16;
	ft_unstostr[env->mod](env, ap);
	if (env->nullarg && env->prec != -100)
	{
		env->index = 0;
		env->tmpbuf[0] = 0;
	}
	ft_apply_specs_hex(env);
	ft_strncpyi_buf(env, env->tmpbuf, &env->pindex, env->index);
	ft_addtobuf_field(env, ' ', env->fill_field);
	ft_addtobuf_prec(env, ' ', env->fill_prec);
}
