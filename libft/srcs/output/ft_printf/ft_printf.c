/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:50:08 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 14:14:40 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf/ft_printf.h"
#include <stdlib.h>
#include <stdio.h>

void		ft_reset_index(t_env *env)
{
	env->pindex = 0;
	env->rindex = 0;
}

static int	ft_convert(void (*tab[128])(t_env *env, char *format, va_list ap),
		t_env *env, char **format, va_list ap)
{
	if (**format && env->color_chars != 5 && env->color_chars != -1)
	{
		if (ft_read_specs(env, (char **)format) == -1)
			return (-1);
		if (env->field == -111 && (env->field = va_arg(ap, int)) < 0)
		{
			env->flags |= 1 << MINUS;
			env->field = ftp_abs(env->field);
		}
		if (env->prec == -111 && (env->prec = va_arg(ap, int)) < 0)
			env->prec = -100;
		if (env->id >= 0)
			tab[(int)env->id](env, (char *)*format, ap);
		if (env->error == 1)
			return (-1);
	}
	return (0);
}

int			ft_endn(t_env *env, unsigned char *str)
{
	int len;

	len = ftp_strlen((char *)str);
	ft_strncpyi_buf(env, str, &env->pindex, len);
	write(env->output, env->buf, env->pindex);
	return (env->rindex += env->pindex);
}

int			ft_printf(const char *format, ...)
{
	static int		times;
	static void		(*tab_conv[128])(t_env *env, char *format, va_list ap);
	static t_env	env;
	va_list			ap;

	if (!times++)
	{
		ft_init_fttab(tab_conv);
		env.output = 1;
		env.prev = -1;
	}
	ft_reset_index(&env);
	va_start(ap, (char *)format);
	while (*format && !ft_clear_form(&env)
			&& ft_read_until_arg(&env, (unsigned char **)&format, ap) != -1)
	{
		if (ft_convert(tab_conv, &env, (char **)&format, ap) == -1)
			if (env.color_chars != -1)
			{
				write(env.output, env.buf, env.pindex);
				return (-1);
			}
	}
	va_end(ap);
	return (ft_endn(&env, (unsigned char *)format));
}
