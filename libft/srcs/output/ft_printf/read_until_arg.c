/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_until_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:56:50 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 15:45:00 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

int		ft_read_until_arg(t_env *env, unsigned char **s2, va_list ap)
{
	env->err_ind = env->pindex;
	env->j = 0;
	if ((env->r = ftp_strcstr((char *)*s2, "%{")) == -1)
		return (-1);
	while (env->r != -1 && *(*s2 + env->r) != '%')
	{
		ft_strncpyi_buf(env, *s2, &env->pindex, env->r);
		*s2 += env->r;
		env->color_chars = ft_check_color(env, (char *)*s2, ap);
		if (env->color_chars == -1)
		{
			env->buf[env->pindex++] = '{';
			++*s2;
		}
		else
			*s2 += env->color_chars;
		env->r = ftp_strcstr((char *)*s2, "%{");
	}
	if (*(*s2 + env->r) == '%')
	{
		ft_strncpyi_buf(env, *s2, &env->pindex, env->r);
		*s2 += env->r;
	}
	return (0);
}
