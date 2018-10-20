/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_cust_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:40:11 by emuckens          #+#    #+#             */
/*   Updated: 2018/04/09 13:39:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <limits.h>

void	ft_ultoa_base_cust(t_env *env, unsigned char *s, unsigned long int num)
{
	unsigned char	*tab;
	int				len;

	tab = (unsigned char *)"0123456789abcdef";
	len = ft_llnblen(num, env->base);
	env->index += len;
	s[len] = '\0';
	while (len--)
	{
		s[len] = tab[num % env->base];
		num /= env->base;
	}
}

void	ft_ulltoa_base_cust(t_env *env, unsigned char *s, unsigned long long n)
{
	unsigned char	*tab;
	int				len;

	tab = (unsigned char *)"0123456789abcdef";
	len = ft_ullnblen(n, env->base);
	env->index += len;
	s[len] = '\0';
	while (len--)
	{
		s[len] = tab[(uintmax_t)n % env->base];
		n /= env->base;
	}
}

void	ft_lltoa_base_cust(t_env *env, unsigned char *s, long long int num)
{
	unsigned char	*tab;
	int				len;

	tab = (unsigned char *)"0123456789abcdef";
	len = ft_llnblen(num, env->base);
	if (num < 0 && num >= -9223372036854775807)
		ft_mng_negative_arg(env, &num);
	if (((env->arg.lli / 10 == -922337203685477580) && env->arg.lli % 10 == -8))
	{
		ft_strncpyi_tmp(env,
			(unsigned char *)"9223372036854775808", &env->index, 19);
		env->prec -= 19;
		env->neg = 1;
		return ;
	}
	env->index += len;
	s[len] = '\0';
	while (len--)
	{
		s[len] = tab[num % env->base];
		num /= env->base;
	}
}

void	ft_uitoa_base_cust(t_env *env, unsigned char *str, unsigned int num)
{
	unsigned char	*tab;
	int				len;

	tab = (unsigned char *)"0123456789abcdef";
	len = ft_unblen(num, env->base);
	env->index += len;
	(str)[len] = '\0';
	while (len--)
	{
		(str)[len] = tab[num % env->base];
		num /= env->base;
	}
}

void	ft_ltoa_base_cust(t_env *env, unsigned char *str, long int num)
{
	unsigned char	*tab;
	int				len;

	len = 0;
	tab = (unsigned char *)"0123456789abcdef";
	if (num < 0)
		ft_mng_negative_arg(env, (long long int *)&num);
	if (env->arg.li / 10 == -922337203685477580 && env->arg.li % 10 == -8)
	{
		ft_strncpyi_tmp(env,
				(unsigned char *)"9223372036854775808", &env->index, 19);
		env->prec -= 19;
		env->neg = 1;
		return ;
	}
	len += ft_llnblen(num, env->base);
	env->index += len;
	(str)[len] = '\0';
	while (len--)
	{
		(str)[len] = tab[num % env->base];
		num /= env->base;
	}
}
