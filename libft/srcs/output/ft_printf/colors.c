/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:03:02 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 14:24:15 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf/ft_printf.h"

int			ft_reset_color(t_env *env)
{
	ft_strncpyi_buf(env, (unsigned char *)"\033[0m", &env->pindex, 6);
	env->rindex -= 4;
	env->prev = -1;
	return (5);
}

static int	ft_check_output(t_env *env, unsigned char **c, char *s, va_list ap)
{
	if (ftp_strnequ(s, "FD!}", 4))
	{
		env->output = (int)*(va_arg(ap, int *));
		return (5);
	}
	else if (ftp_strnequ(s, "EOO}", 4))
	{
		write(env->output, env->buf, env->pindex);
		env->pindex = 0;
		env->output = 1;
		if (env->prev != -1)
		{
			ft_strncpyi_buf(
				env, (unsigned char *)c[env->prev], &env->pindex, 10);
			env->rindex -= 8;
		}
		else
			return (ft_reset_color(env));
	}
	else if (ftp_strnequ(s, "EOC}", 4))
		return (ft_reset_color(env));
	return (0);
}

static int	ft_check_list(t_env *env, char *colors[], char *codes[], char *str)
{
	while (env->k < 16)
	{
		if (ftp_strnequ(str, colors[env->k], env->cc))
		{
			ft_strncpyi_buf(
				env, (unsigned char *)codes[env->k], &env->pindex, 10);
			env->rindex -= 8;
			if (env->prev == -1)
				env->prev = env->k;
			return (env->cc + 2);
		}
		++env->k;
	}
	return (-1);
}

int			ft_check_color(t_env *env, char *str, va_list ap)
{
	static char	color[10];
	static char *colors[16] = {"BLACK}", "DRED}", "GREEN}", "BROWN}", "BLUE}",
		"PINK}", "CYAN}", "GREY}", "DGREY}", "LRED}", "LGREEN}", "YELLOW}",
		"LBLUE}", "LPINK}", "LCYAN}", "WHITE}"};
	static char *codes[16] = {"\033[22;30m", "\033[22;31m", "\033[22;32m",
		"\033[22;33m", "\033[22;34m", "\033[22;35m", "\033[22;36m",
		"\033[22;37m", "\033[01;30m", "\033[01;31m", "\033[01;32m",
		"\033[01;33m", "\033[01;34m", "\033[01;35m", "\033[01;36m",
		"\033[01;37m"};

	(void)ap;
	env->cc = -1;
	env->k = 0;
	++str;
	if (!ftp_isalpha(str[env->cc + 1]))
		return (-1);
	while (str[++env->cc] != '}' && env->cc < 10)
		(color)[env->cc] = str[env->cc];
	color[env->cc] = str[env->cc];
	if (env->cc < 3 || env->cc > 7)
		return (-1);
	if (ft_check_output(env, (unsigned char **)codes, color, ap))
		return (5);
	return (ft_check_list(env, colors, codes, color));
}
