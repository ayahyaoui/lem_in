/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_adress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 06:08:51 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/15 03:21:01 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_address_null(t_printf pr)
{
	int		t;
	char	res[1024];

	t = (pr.precis == 0) ? 2 : 3;
	t = (pr.larg > 3) ? pr.larg : t;
	ft_memset(res, ' ', t);
	if (pr.flag_2 != MOINS && pr.precis != 0)
	{
		res[t - 1] = '0';
		res[t - 2] = 'x';
		res[t - 3] = '0';
	}
	else if (pr.flag_2 != MOINS && pr.precis == 0)
	{
		res[t - 1] = 'x';
		res[t - 2] = '0';
	}
	else
	{
		res[0] = '0';
		res[1] = 'x';
		if (pr.precis != 0)
			res[2] = '0';
	}
	return (write(1, res, t));
}

int		ft_put_address(void *ptr, t_printf pr)
{
	long long	x;
	char		*str;
	char		*s;
	int			t;

	x = (long long)ptr;
	if (x == 0 || pr.precis == 0)
		return (ft_address_null(pr));
	if (!(s = ft_memalloc(42)))
		exit(0);
	s[0] = '%';
	if (pr.flag_2 == MOINS)
		s = ft_strcat(s, "-");
	s = ft_strcat(s, "#");
	if (pr.larg >= 0)
	{
		str = ft_itoa(pr.larg);
		s = ft_strcat(s, str);
		free(str);
	}
	s = ft_strcat(s, "llx");
	t = ft_printf(s, x);
	free(s);
	return (t);
}
