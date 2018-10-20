/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_n.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 18:52:10 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 14:48:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_n(t_env *env, char *format, va_list ap)
{
	int		*ptr;

	(void)format;
	ptr = (int *)va_arg(ap, int *);
	*ptr = env->pindex;
}
