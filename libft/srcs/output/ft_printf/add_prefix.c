/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:16:55 by emuckens          #+#    #+#             */
/*   Updated: 2018/06/25 18:50:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_add_prefix_uns(t_env *env)
{
	if (env->prec != -100 || env->prec == -100)
		ft_addtobuf(env, '0', 1);
	ft_addtobuf(env, env->id, 1);
}

void	ft_add_prefix_oct(t_env *env)
{
	if (env->tmpbuf[0] && !env->nullarg)
	{
		ft_addtobuf(env, '0', 1);
		if (env->fill_prec <= 0)
			env->fill_field--;
		env->fill_prec--;
	}
}

void	ft_add_prefix_hex(t_env *env)
{
	if (env->tmpbuf[0] && !env->nullarg)
	{
		ft_addtobuf(env, '0', 1);
		if (env->fill_field > 0)
			env->fill_field--;
		ft_addtobuf_field(env, env->id, 1);
	}
}

void	ft_add_prefix_ptr(t_env *env)
{
	ft_addtobuf(env, '0', 1);
	ft_addtobuf(env, 'x', 1);
}
