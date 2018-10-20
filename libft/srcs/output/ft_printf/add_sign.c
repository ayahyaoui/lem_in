/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sign.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:26:32 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 14:11:40 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_addsign_wzero(t_env *env)
{
	if (env->neg)
		ft_addtobuf_field(env, '-', 1);
	else if (env->flags & 1 << PLUS)
		ft_addtobuf_field(env, '+', 1);
	if (env->prec == -99)
		ft_addtobuf(env, '0', 1);
}

void	ft_addsign_nozero(t_env *env)
{
	if (env->neg)
		ft_addtobuf_field(env, '-', 1);
	else if (env->flags & 1 << PLUS)
		ft_addtobuf(env, '+', 1);
}
