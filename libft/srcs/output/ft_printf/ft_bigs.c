/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:51:03 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 14:47:08 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf/ft_printf.h"

void		ft_convert_wc(t_env *env, int len)
{
	int tmplen;

	tmplen = 0;
	while (++env->i < len && !env->error && env->prec != 0)
	{
		tmplen = ft_putwchar(env, env->arg.wcs[env->i]);
		if (MB_CUR_MAX == 1)
		{
			if (env->index < env->prec || env->prec == -100 || env->prec == 0)
				ft_strncpyi_wbuf(env, env->wtmp, &env->index, 1);
		}
		else if (env->index + tmplen <= env->prec || env->prec == -100)
			ft_strncpyi_wbuf(env, env->wtmp, &env->index, tmplen);
	}
}

void		ft_bigs(t_env *env, char *format, va_list ap)
{
	int len;

	(void)format;
	len = 0;
	env->i = -1;
	env->arg.wcs = va_arg(ap, wchar_t *);
	if (env->arg.wcs)
		while (env->arg.wcs[len])
			++len;
	if (env->arg.wcs == NULL)
		ft_strncpyi_buf(env, (unsigned char *)"(null)", &env->pindex, 6);
	else
		ft_convert_wc(env, len);
	if (!env->error || env->prec == 1)
	{
		env->field -= env->index;
		ft_apply_specs_wcs(env);
		ft_strncpyi_buf(env, env->wbuf, &env->pindex, env->index);
		ft_addtobuf_field(env, ' ', env->fill_field);
	}
}
