/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:39:49 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/09 03:38:55 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_printf	init_pr(void)
{
	t_printf pr;

	pr.larg = -1;
	pr.precis = -1;
	pr.flag_1 = 0;
	pr.flag_2 = 0;
	pr.flag_3 = 0;
	pr.maj = 0;
	return (pr);
}

int			ft_isspec(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}

int			ft_secure(char *str)
{
	int i;

	i = 0;
	while (ft_isflag(str[i]))
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		while (ft_isdigit(str[++i]))
			;
	while (str[i] && ft_isspec(str[i]))
		i++;
	if (ft_istype(str[i]) == 0)
		return (-1);
	return (1);
}

int			ft_istype(char c)
{
	if (c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'p' || c == 'S' ||
		c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'O' || c == 'D' ||
		c == 'U' || c == '%' || c == 'C' || c == 'S')
		return (1);
	return (0);
}
