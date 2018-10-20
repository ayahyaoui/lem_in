/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 12:36:57 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 14:11:56 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_mng_flags(t_env *env)
{
	if (env->flags & 1 << ZERO)
		if (env->flags & 1 << MINUS
				|| (env->prec > -99
					&& env->id != '%'
					&& env->id != 'f'
					&& env->id != 'b'
					&& env->id != 'c')
				|| env->field == -111)
			env->flags -= 1 << ZERO;
	if (env->flags & 1 << SPACE && (env->flags & 1 << PLUS || !env->id))
		env->flags -= 1 << SPACE;
}

int		ft_is_mod(unsigned char c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == 'L');
}

int		ft_is_flag(unsigned char c)
{
	return (c == '#' || c == '0' || c == ' ' || c == '+' || c == '-');
}

void	ft_strcapitalize(unsigned char *str)
{
	while (*str)
	{
		*str = ftp_toupper(*str);
		str++;
	}
}
