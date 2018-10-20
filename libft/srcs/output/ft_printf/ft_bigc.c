/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:49:00 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 14:12:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf/ft_printf.h"

void	ft_bigc(t_env *env, char *format, va_list ap)
{
	int		tmplen;

	tmplen = 0;
	(void)format;
	env->fill_field = 0;
	env->fill_prec = 0;
	env->arg.wc = va_arg(ap, wchar_t);
	if (env->arg.wc == 0)
		ft_addtobuf(env, 0, 1);
	else
	{
		format += (tmplen = ft_putwchar(env, env->arg.wc));
		if (!env->error || env->arg.wc > 1114111)
		{
			ft_apply_specs_char(env);
			ft_strncpyi_buf(env, env->wtmp, &env->pindex, tmplen);
			if (env->fill_field > env->fill_prec)
				ft_addtobuf_field(env, ' ', env->fill_field);
		}
	}
}
