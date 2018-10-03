/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 21:21:54 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/17 00:57:30 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**					ft_put_base si # alors
**							si base 16 flag_3 = 2
**							si base 8 flag_3 = 1
**					t = taille
**					si base == 8 et taille < precision
**							flag_3 = 0
**					t = nouvelle taille (si la percision est > taille)
**					si le flag est 0 et la largeur est sup a la taille
**							on ajoute une precision = largeur - flag_3
**					on ajoute a la taille flag 3
**===============================================================
**					on a la taille
*/

void	ft_put_space(long long x, t_printf pr, int size, int base)
{
	char	*str;
	int		t;

	t = base / 100;
	base = base % 100;
	if (!(str = (char *)malloc(sizeof(char) * (t + 1))))
		exit(0);
	str = ft_memset(str, ' ', t);
	if (pr.flag_2 == ZERO)
		str = ft_memset(str, '0', t);
	write(1, str, t);
	pr.larg = -1;
	free(str);
	if (pr.flag_2 != MOINS)
		ft_put_base(x, pr, size, base);
}

char	*ft_put_base2(t_printf pr, int t2, int base, int t)
{
	char *res;

	if (!(res = ft_memalloc(t + 42)))
		exit(0);
	(void)base;
	if (pr.flag_3)
		res[0] = '0';
	if (pr.flag_3 == 2)
		res[1] = 'x' - 32 * pr.maj;
	if ((pr.precis) > t2)
		ft_memset(&res[pr.flag_3], '0', pr.precis - t2);
	return (res);
}

int		ft_put_base(long long x, t_printf pr, int size, int base)
{
	char	*res;
	int		t;

	if (x == 0)
		return (ft_putstr_null(pr, (base == 16) ? OptHexa : OptOctal));
	pr.flag_3 = (pr.flag_3) ? 1 + base / 16 : pr.flag_3;
	t = ft_lenbase2(x, base, size);
	pr.flag_3 = (pr.flag_3 == 1 && t < pr.precis) ? 0 : pr.flag_3;
	t = (t < pr.precis) ? pr.precis : t;
	t += pr.flag_3;
	if (pr.flag_2 == ZERO && pr.larg > t)
	{
		pr.precis = pr.larg - pr.flag_3;
		t = pr.larg;
	}
	if ((pr.larg <= t) || (pr.flag_2 == MOINS))
	{
		res = ft_put_base2(pr, ft_lenbase2(x, base, size), base, t);
		res = ft_strfreecat(res, ft_itoa_base2(x, base, size, pr.maj));
		write(1, res, t);
		free(res);
	}
	if (pr.larg > t)
		ft_put_space(x, pr, size, (pr.larg - t) * 100 + base);
	return ((t < pr.larg) ? pr.larg : t);
}
