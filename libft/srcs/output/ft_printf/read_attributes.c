/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_attributes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 12:34:25 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 14:31:03 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <unistd.h>

static void	ft_read_mod(t_env *env, char **str)
{
	int		i;
	char	mod_str[3];

	i = 0;
	while (i < 2)
	{
		if (ft_is_mod((*str)[i]) && (i == 0 || (*str)[i] == (mod_str)[i - 1]))
		{
			mod_str[i] = (*str)[i];
			++i;
		}
		else
			break ;
	}
	mod_str[i] = 0;
	env->mod = (ftp_strequ(mod_str, "h")) ? H : env->mod;
	env->mod = (ftp_strequ(mod_str, "hh")) ? HH : env->mod;
	env->mod = (ftp_strequ(mod_str, "l")) ? L : env->mod;
	env->mod = (ftp_strequ(mod_str, "ll")) ? LL : env->mod;
	env->mod = (ftp_strequ(mod_str, "L")) ? NOMOD : env->mod;
	env->mod = (ftp_strequ(mod_str, "z")) ? Z : env->mod;
	env->mod = (ftp_strequ(mod_str, "j")) ? J : env->mod;
	*str += i;
}

static int	ft_read_flags(t_env *env, char **str)
{
	int						add_flags;
	static unsigned char	ref[] = "#0- +";

	env->i = -1;
	env->j = 0;
	add_flags = 0;
	while (ft_is_flag((*str)[env->j]))
	{
		while (++env->i < 5)
			if (ref[env->i] == (*str)[env->j])
			{
				env->flags |= 1 << env->i;
				++add_flags;
			}
		++env->j;
		env->i = -1;
	}
	(*str) += add_flags;
	return (0);
}

static void	ft_read_field(t_env *env, char **str)
{
	if (**str == '*')
	{
		env->field = -111;
		++(*str);
	}
	else
		while (ftp_isdigit(**str))
		{
			env->field = 10 * (env->field) + (**str - '0');
			++(*str);
		}
}

static void	ft_read_precision(t_env *env, char **str)
{
	int prec;

	prec = 0;
	if (**str == '.')
	{
		++prec;
		++(*str);
	}
	env->prec = (**str == '.') ? 0 : env->prec;
	if (**str == '*')
	{
		env->prec = -111;
		++(*str);
	}
	else if (**str != '.' && prec)
	{
		while (ftp_isdigit(**str))
			env->prec =
				10 * (env->prec == -100 ? 0 : env->prec) + (*((*str)++) - '0');
		if (env->prec == -100 && !ftp_isdigit(*(*str - 1))
			&& *(*str - 1) != '%' && !ft_is_flag(*(*str - 1)))
			env->prec = -99;
	}
}

int			ft_read_specs(t_env *env, char **str)
{
	++(*str);
	while (**str && **str == '{')
	{
		env->buf[env->index++] = '{';
		++(*str);
	}
	ft_read_flags(env, str);
	ft_read_field(env, str);
	ft_read_precision(env, str);
	if (ft_is_mod(**str))
		ft_read_mod(env, str);
	env->id = *(*str);
	if (**str)
		++(*str);
	if ((env->id && !ftp_isalpha(env->id) && env->id != '%')
			|| ft_is_mod(env->id)
			|| ft_is_flag(env->id))
		return (-1);
	ft_mng_flags(env);
	return (0);
}
