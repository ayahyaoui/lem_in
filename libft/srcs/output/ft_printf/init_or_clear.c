/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_or_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:45:42 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/03 17:15:50 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void		ft_setzero(unsigned char str[], int len, char c)
{
	int		i;

	i = 0;
	while (i < len)
	{
		str[i] = c;
		++i;
	}
}

void		ft_init_fttab(
		void (*tab_conv[128])(t_env *env, char *s, va_list ap))
{
	int i;

	i = 0;
	while (i < 128)
		tab_conv[i++] = &ft_noconv;
	tab_conv['d'] = &ft_d;
	tab_conv['i'] = &ft_i;
	tab_conv['o'] = &ft_o;
	tab_conv['u'] = &ft_u;
	tab_conv['x'] = &ft_x;
	tab_conv['X'] = &ft_bigx;
	tab_conv['c'] = &ft_c;
	tab_conv['C'] = &ft_bigc;
	tab_conv['s'] = &ft_s;
	tab_conv['S'] = &ft_bigs;
	tab_conv['D'] = &ft_bigd;
	tab_conv['O'] = &ft_bigo;
	tab_conv['U'] = &ft_bigu;
	tab_conv['p'] = &ft_p;
	tab_conv['b'] = &ft_b;
	tab_conv['n'] = &ft_n;
}

int			ft_clear_form(t_env *env)
{
	env->field = 0;
	env->prec = -100;
	env->id = -1;
	env->mod = 0;
	env->arg.i = 0;
	env->index = 0;
	env->i = 0;
	env->j = 0;
	env->k = 1;
	env->fill_field = 0;
	env->fill_prec = 0;
	env->neg = 0;
	env->flags = 0;
	env->base = 10;
	env->nullarg = 0;
	env->color_chars = 0;
	env->err_ind = !env->error ? 0 : env->err_ind;
	env->r = 0;
	env->cc = -1;
	env->error = 0;
	return (0);
}
