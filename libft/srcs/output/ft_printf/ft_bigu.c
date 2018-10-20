/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:41:34 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 14:47:14 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_bigu(t_env *env, char *format, va_list ap)
{
	(void)format;
	env->mod = L;
	env->id = 'u';
	ft_u(env, format, ap);
}
