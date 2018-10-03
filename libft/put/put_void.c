/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_void.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 19:24:00 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/15 00:02:55 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

#define LARG_MAX 1024

int		ft_putstr_null(t_printf pr, int spe)
{
	char	tab[LARG_MAX];
	int		t;
	int		sp;

	t = (pr.larg > 1) ? pr.larg : 1;
	if (pr.flag_2 == ZERO)
		pr.precis = t;
	if (pr.precis > t)
		t = pr.precis;
	ft_memset(tab, '0', t + 1);
	sp = (pr.precis > 1) ? t - pr.precis : t - 1;
	if (sp && pr.flag_2 == MOINS)
		ft_memset(&tab[t - sp], ' ', sp);
	else if (sp)
		ft_memset(tab, ' ', sp);
	if ((spe != OptOctal || pr.flag_3 == 0) && pr.precis == 0)
		ft_memset(tab, ' ', t);
	if ((spe != OptOctal || pr.flag_3 == 0) && pr.precis == 0 && t == 1)
		t = 0;
	if (t == 1 && spe == OptInt && pr.flag_1 == PLUS && t++)
		tab[0] = '+';
	return (write(1, tab, t));
}

int		ft_put_void(t_printf pr)
{
	char *res;

	if (pr.larg == -1 || pr.larg == 1 || (pr.flag_2 == MOINS))
		write(1, "%", 1);
	if (pr.larg > 1)
	{
		if (!(res = ft_memalloc(pr.larg + 2)))
			exit(0);
		res = (pr.flag_2 != ZERO) ? ft_memset(res, ' ', pr.larg) :
									ft_memset(res, '0', pr.larg);
		if (pr.flag_2 != MOINS)
		{
			res[pr.larg - 1] = '%';
			write(1, res, pr.larg);
		}
		else
			write(1, res, pr.larg - 1);
		free(res);
	}
	return ((pr.larg != -1) ? pr.larg : 1);
}
