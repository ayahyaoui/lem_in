/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 23:58:07 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/15 03:44:14 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**		meme chose que arg_1
*/

t_option	*ft_opt_void(t_option *l, const char *kw, int (*f)(t_printf))
{
	t_option *li;

	if (!(li = (t_option *)malloc(sizeof(t_option))))
		return (0x0);
	li->keyword = kw;
	li->spec = OptVoid;
	li->fct.opt_void = f;
	li->next = l;
	return (li);
}

t_option	*ft_opt_base(t_option *l, const char *kw,
		int (*f)(long long, t_printf, int, int))
{
	t_option *li;

	if (!(li = (t_option *)malloc(sizeof(t_option))))
		return (0x0);
	li->keyword = kw;
	li->spec = OptBase;
	li->fct.opt_base = f;
	li->next = l;
	return (li);
}

t_option	*ft_opt_adress(t_option *l, const char *kw,
			int (*f)(void*, t_printf))
{
	t_option *li;

	if (!(li = (t_option *)malloc(sizeof(t_option))))
		return (0x0);
	li->keyword = kw;
	li->spec = OptAddress;
	li->fct.opt_address = f;
	li->next = l;
	return (li);
}

t_option	*ft_opt_w_char(t_option *l, const char *kw,
		int (*f)(int, t_printf, int t))
{
	t_option *li;

	if (!(li = (t_option *)malloc(sizeof(t_option))))
		return (0x0);
	li->keyword = kw;
	li->spec = OptWChar;
	li->fct.opt_w_char = f;
	li->next = l;
	return (li);
}
