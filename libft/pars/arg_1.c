/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 23:58:07 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/12 06:28:45 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**		ft_opt... contient:
**			l : une liste d'option
**			kw : keyword (Sring)
**			f : une fonction
**		ajoute ... a la liste des option
*/

t_option	*ft_opt_string(t_option *l, const char *kw,
		int (*f)(const char*, t_printf))
{
	t_option *li;

	if (!(li = (t_option *)malloc(sizeof(t_option))))
		return (0x0);
	li->keyword = kw;
	li->spec = OptString;
	li->fct.opt_str = f;
	li->next = l;
	return (li);
}

t_option	*ft_opt_w_string(t_option *l, const char *kw,
		int (*f)(wchar_t*, t_printf))
{
	t_option *li;

	if (!(li = (t_option *)malloc(sizeof(t_option))))
		return (0x0);
	li->keyword = kw;
	li->spec = OptString;
	li->fct.opt_w_str = f;
	li->next = l;
	return (li);
}

t_option	*ft_opt_unsigned_long_long_int(t_option *l, const char *kw,
		int (*f)(unsigned long long, t_printf))
{
	t_option *li;

	if (!(li = (t_option *)malloc(sizeof(t_option))))
		return (0x0);
	li->keyword = kw;
	li->spec = OptUnsignedLongInt;
	li->fct.opt_unsigned_long_long_int = f;
	li->next = l;
	return (li);
}
