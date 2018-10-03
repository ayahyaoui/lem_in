/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunsigned_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 18:19:01 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/09 00:26:07 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_longlong(char *res, long long x, size_t t, int type)
{
	res = ft_memset(res, '0', t + 1);
	if (type == 1)
		ft_unsignedlonglongnbr(res, x, t);
	if (type == 2)
		ft_longlongnbr(res, x, t);
}

size_t	taille_unsignedlonglongnbr(unsigned long long x, size_t t,
		t_printf pr)
{
	if (x == 0 && pr.precis == 0 && t == 1)
		return (0);
	while ((x = x / 10) > 0)
		t++;
	if ((int)t < pr.precis)
		t = pr.precis;
	if (pr.flag_1 != 0)
		t++;
	return (t);
}

void	ft_unsignedlonglongnbr(char *res, unsigned long long x, size_t t)
{
	if (x > 0)
	{
		res[t] = '0' + x % 10;
		ft_unsignedlonglongnbr(res, x / 10, t - 1);
	}
}

int		ft_put_unsignedlonglongint(unsigned long long x, t_printf pr)
{
	char		*res;
	int			t;

	pr.flag_1 = 0;
	t = taille_unsignedlonglongnbr(x, 1, pr);
	if (pr.flag_2 == ZERO && pr.larg > (int)t)
	{
		pr.precis = pr.larg;
		t = pr.precis;
	}
	if (pr.larg <= t || pr.flag_2 == MOINS)
	{
		if (!(res = (char *)malloc(sizeof(char) * (t + 2))))
			exit(0);
		ft_longlong(res, x, t, 1);
		if (pr.flag_1 == 0)
			write(1, &res[1], t);
		else
			write(1, res, t + 1);
		free(res);
	}
	if (pr.larg > t)
		ft_put_longlongint_larg(x, pr, pr.larg - t, 1);
	return ((t < pr.larg) ? pr.larg : t);
}
