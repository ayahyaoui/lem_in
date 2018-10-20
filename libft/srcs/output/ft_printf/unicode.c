/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:28:24 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/18 11:03:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

static unsigned int	ft_setmask(unsigned int n, int bytes)
{
	unsigned int	mask;

	mask = n;
	if (bytes == 2)
		mask = 49280;
	if (bytes == 3)
		mask = 14712960;
	if (bytes == 4)
		mask = 4034953344;
	return (mask);
}

static unsigned int	ft_putinmask(unsigned int n, int bytes)
{
	int		mask;
	int		i;

	i = 0;
	mask = ft_setmask(n, bytes);
	while (n)
	{
		mask |= ((n & 0x3F) << (i++ * 8));
		n >>= 6;
	}
	return (mask);
}

static int			ft_mng_unicode_err(t_env *env, int bytes)
{
	env->error = 1;
	env->fill_field -= bytes;
	env->pindex = env->err_ind;
	return (bytes);
}

static int			ft_check_and_mask(t_env *env, int *n, int *bytes)
{
	unsigned int n_cpy;

	n_cpy = (unsigned int)*n;
	if (*n > 0x7FF)
	{
		while (n_cpy)
		{
			n_cpy >>= 8;
			(*bytes)++;
		}
		(*bytes)++;
	}
	*n = ft_putinmask(*n, *bytes);
	env->fill_field -= *bytes;
	return (0);
}

unsigned int		ft_putwchar(t_env *env, int n)
{
	unsigned int	c;
	int				bytes;
	unsigned char	test;
	int				i;

	i = 0;
	c = 0xFF;
	bytes = 0;
	if (n < 0x7FF)
		bytes = (n < 128 || MB_CUR_MAX == 1) ? 1 : 2;
	if ((n > 255 && MB_CUR_MAX == 1 && env->prec != 1)
		|| n < 0 || (n > 55295 && n < 57344) || n > 1114111)
		return (ft_mng_unicode_err(env, bytes));
	if (ft_check_and_mask(env, &n, &bytes) > (int)MB_CUR_MAX)
		return (bytes);
	i = bytes;
	while (--i >= 0)
	{
		if (n != 0)
			if ((test = (unsigned char)n & c) != 0)
				env->wtmp[i] = (unsigned char)test;
		n >>= 8;
	}
	return (bytes);
}
