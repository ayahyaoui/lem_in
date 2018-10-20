/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_specs_cs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:06:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/03 16:26:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_apply_specs_char(t_env *env)
{
	env->fill_field += env->field;
	env->fill_prec += env->prec;
	if (~env->flags & 1 << MINUS)
		ft_addtobuf_switch(env, env->fill_field);
}

void	ft_apply_specs_str(t_env *env)
{
	if (env->prec <= 0 && env->prec != -99)
		env->fill_field += (env->field
				- (env->str ? ftp_strlen((char *)env->str) : 0));
	else
		env->fill_field += (env->field - env->index);
	if (~env->flags & 1 << MINUS)
		ft_addtobuf_switch(env, env->fill_field);
}

void	ft_apply_specs_wcs(t_env *env)
{
	env->fill_field = env->field;
	if (~env->flags & 1 << MINUS)
		ft_addtobuf_switch(env, env->field);
}
