/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:40:18 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/29 13:55:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_bigo(t_env *env, char *format, va_list ap)
{
	(void)format;
	env->mod = L;
	env->id = 'o';
	ft_o(env, format, ap);
}
