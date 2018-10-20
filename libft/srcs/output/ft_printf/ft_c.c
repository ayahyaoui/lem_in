/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:47:35 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 13:34:53 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_c(t_env *env, char *format, va_list ap)
{
	(void)format;
	if (env->mod == L)
		ft_bigc(env, format, ap);
	else
	{
		env->arg.c = va_arg(ap, int);
		env->tmpbuf[0] = env->arg.c;
		env->tmpbuf[1] = 0;
		env->field--;
		ft_apply_specs_char(env);
		if (env->arg.c == 0)
			ft_addtobuf(env, 0, 1);
		else
			env->buf[env->pindex++] = env->tmpbuf[0];
		ft_addtobuf(env, ' ', env->fill_field);
	}
}
