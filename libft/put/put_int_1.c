/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putint_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 18:19:09 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/14 07:06:21 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#define ABS(x) ((x < 0) ? (x * -1) : (x))

void	ft_put_longlongint_larg(long long x, t_printf pr, int t, int type)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (t + 1))))
		exit(0);
	str = ft_memset(str, ' ', t);
	if (pr.flag_2 == ZERO)
		str = ft_memset(str, '0', t);
	write(1, str, t);
	pr.larg = -1;
	free(str);
	if (pr.flag_2 != MOINS && type == 2)
		ft_put_longlongint(x, pr);
	if (pr.flag_2 != MOINS && type == 1)
		ft_put_unsignedlonglongint((uintmax_t)x, pr);
}

void	ft_longlongnbr(char *res, long long x, size_t t)
{
	res[t + 1] = '\0';
	if (x < 0)
	{
		res[0] = '-';
		res[t--] = '0' + ABS(x % 10);
		x /= 10;
		x *= -1;
	}
	ft_unsignedlonglongnbr(res, x, t);
}

size_t	taille_longlongnbr(long long x, size_t t, t_printf pr)
{
	t = 1;
	if (x == 0 && pr.precis == 0)
		t = 0;
	if (x < 0)
	{
		t = 3;
		if (x < -99)
			x = (x / 10) * -1;
		else
		{
			t--;
			x = x * -1;
		}
		pr.flag_1 = 0;
	}
	return (taille_unsignedlonglongnbr((uintmax_t)x, t, pr));
}

void	ft_put_longlongint2(long long x, t_printf pr, int t)
{
	char *res;

	if (!(res = (char *)malloc(sizeof(char) * (t + 2))))
		exit(0);
	if (t)
		ft_longlong(res, x, t - 1, 2);
	if (pr.flag_1 == SPACE && x >= 0)
		res[0] = ' ';
	else if (pr.flag_1 == PLUS && x >= 0)
		res[0] = '+';
	write(1, res, t);
	free(res);
}

int		ft_put_longlongint(long long x, t_printf pr)
{
	int	t;

	t = (int)taille_longlongnbr(x, 1, pr);
	if ((pr.precis < t - 1) || (((pr.flag_1 == 0 || x < 0) && pr.precis < t)))
		pr.precis = -1;
	if ((x < 0 && pr.precis > 0))
		t++;
	if (pr.flag_2 == ZERO && pr.larg > (int)t)
	{
		pr.precis = pr.larg;
		t = pr.precis;
	}
	if ((pr.larg <= t) || (pr.flag_2 == MOINS))
		ft_put_longlongint2(x, pr, t);
	if (pr.larg > t)
		ft_put_longlongint_larg(x, pr, pr.larg - t, 2);
	return ((t < pr.larg) ? pr.larg : t);
}
