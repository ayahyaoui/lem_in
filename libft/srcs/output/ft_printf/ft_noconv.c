/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_noconv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:52:08 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 14:48:32 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void			ft_noconv(t_env *env, char *format, va_list ap)
{
	(void)ap;
	(void)format;
	if (env->id)
	{
		if (env->nullarg)
			env->tmpbuf[0] = (env->prec == -100) ? '0' : 0;
		env->fill_field = env->field - 1;
		if (~env->flags & 1 << MINUS)
			ft_addtobuf_switch(env, env->fill_field);
		if (env->id && env->id != '%')
			env->field--;
		env->buf[env->pindex++] = env->id;
		ft_addtobuf_switch(env, env->fill_field);
	}
}
