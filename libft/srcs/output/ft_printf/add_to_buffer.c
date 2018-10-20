/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:01:48 by emuckens          #+#    #+#             */
/*   Updated: 2018/06/25 18:50:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <unistd.h>

void	ft_addtobuf(t_env *env, char c, int times)
{
	env->i = 0;
	while (env->i++ < times)
	{
		if (env->pindex >= BUFF_SIZE)
		{
			write(1, env->buf, BUFF_SIZE);
			env->rindex += env->pindex;
			env->pindex = 0;
		}
		env->buf[env->pindex++] = c;
	}
}

void	ft_addtobuf_field(t_env *env, char c, int times)
{
	ft_addtobuf(env, c, times);
	env->fill_field -= times;
}

void	ft_addtobuf_prec(t_env *env, char c, int times)
{
	ft_addtobuf(env, c, times);
	env->fill_prec -= times;
}

void	ft_addtobuf_switch(t_env *env, int times)
{
	if (env->flags & 1 << ZERO)
		ft_addtobuf_field(env, '0', times);
	else
		ft_addtobuf_field(env, ' ', times);
}
