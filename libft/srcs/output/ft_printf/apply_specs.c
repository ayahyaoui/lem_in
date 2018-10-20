/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_specs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 11:43:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 14:11:52 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void			ft_apply_specs_int(t_env *env)
{
	if (env->nullarg)
		mng_nullarg(env);
	env->fill_field += (env->field - ftp_maxint(env->prec, env->index));
	if (env->prec > 0)
		env->fill_prec += (env->prec - env->index);
	if (env->flags & 1 << ZERO)
		ft_addsign_wzero(env);
	else if ((env->flags & 1 << PLUS && !env->neg)
			|| (env->neg && ~env->flags & 1 << MINUS))
		env->fill_field--;
	if (env->flags & 1 << SPACE && !env->neg)
		ft_addtobuf_field(env, ' ', 1);
	if (~env->flags & 1 << MINUS)
		ft_addtobuf_switch(env, env->fill_field);
	if (~env->flags & 1 << ZERO)
		ft_addsign_nozero(env);
	if (~env->flags & 1 << MINUS || ~env->flags & 1)
		ft_addtobuf(env, '0', env->fill_prec);
	if (env->flags & (1 << ZERO))
		ft_addtobuf_field(env, '0', env->fill_field);
}

void			ft_apply_specs_hex(t_env *env)
{
	env->fill_field += (env->field - ftp_maxint(env->prec, env->index));
	env->fill_prec += (env->prec - env->index);
	if (env->flags & 1 << ZERO && env->flags & 1 << POUND && env->prec != -99)
		ft_add_prefix_hex(env);
	if (~env->flags & 1 << MINUS && env->fill_field > 0)
	{
		env->j = 0;
		if (env->flags & 1 << POUND && ~env->flags & (1 << ZERO))
			if (!env->nullarg && env->prec != -99)
				env->fill_field -= 2;
		if (env->flags & 1 << ZERO && env->prec != -99)
			ft_addtobuf_field(env, '0', env->fill_field);
		else
			ft_addtobuf_field(env, ' ', env->fill_field);
	}
	if (~env->flags & 1 << ZERO && env->flags & 1 << POUND)
		ft_add_prefix_hex(env);
	ft_addtobuf_prec(env, '0', env->fill_prec);
	if (env->flags & 1 << ZERO)
		ft_addtobuf_field(env, '0', env->fill_field);
}

void			ft_apply_specs_oct(t_env *env)
{
	env->fill_field += (env->field - ftp_maxint(env->prec, env->index));
	env->fill_prec += (env->prec - env->index);
	if (env->flags & 1 << ZERO && env->flags & 1 << POUND && env->prec != -99)
		ft_add_prefix_oct(env);
	if (~env->flags & 1 << MINUS && env->fill_field > 0)
	{
		env->j = 0;
		if (env->flags & 1 << POUND && ~env->flags & (1 << ZERO))
			if (!env->nullarg && env->fill_prec < 0 && env->prec != -99)
				env->fill_field -= 1;
		if (env->flags & 1 << ZERO && env->prec != -99)
			ft_addtobuf_field(env, '0', env->fill_field);
		else
			ft_addtobuf_field(env, ' ', env->fill_field);
	}
	if (~env->flags & 1 << ZERO && env->flags & 1 << POUND)
		ft_add_prefix_oct(env);
	ft_addtobuf_prec(env, '0', env->fill_prec);
	if (env->flags & 1 << ZERO)
		ft_addtobuf_field(env, '0', env->fill_field);
}

void			ft_apply_specs_uns(t_env *env)
{
	env->fill_field += (env->field - ftp_maxint(env->prec, env->index));
	env->fill_prec += (env->prec - env->index);
	if (~env->flags & 1 << MINUS && env->fill_field > 0)
	{
		env->j = 0;
		if (env->flags & 1 << POUND && ~env->flags & (1 << ZERO) && env->prec)
			if (!env->nullarg && (env->flags & 1 << ZERO || env->prec != -99))
				env->fill_field -= 2;
		if (env->flags & 1 << ZERO && env->prec != -99)
			ft_addtobuf_field(env, '0', env->fill_field);
		else
			ft_addtobuf_field(env, ' ', env->fill_field);
	}
	if (env->fill_prec >= 0)
		ft_addtobuf_prec(env, '0', env->fill_prec);
	if (env->fill_field > 0 && env->flags & 1 << ZERO)
		ft_addtobuf_field(env, '0', env->fill_field);
}

void			ft_apply_specs_ptr(t_env *env)
{
	if (env->nullarg)
	{
		if (env->prec == -100)
			env->tmpbuf[0] = '0';
		else
		{
			env->tmpbuf[0] = 0;
			env->index = 0;
		}
	}
	env->fill_field += (env->field - ftp_maxint(env->prec, env->index) - 2);
	env->fill_prec += (env->prec - env->index);
	if (env->flags & 1 << ZERO)
		ft_add_prefix_ptr(env);
	if (~env->flags & 1 << MINUS)
		ft_addtobuf_switch(env, env->fill_field);
	if ((~env->flags & 1 << ZERO))
		ft_add_prefix_ptr(env);
	ft_addtobuf_prec(env, '0', env->fill_prec);
}
