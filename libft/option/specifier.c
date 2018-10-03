/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 04:29:01 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/15 03:43:09 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**		ft_spe recupere:
**			str: une string contenant toute les infos
**		retourne la specifier du str
*/

int			ft_spe2(char *str)
{
	int l;
	int i;

	i = 0;
	l = 0;
	if (*str == 'j' || *str == 'z')
		return (ft_spe_base(str + 1, 2));
	while (str[i] && !ft_istype(str[i]))
	{
		if (str[i] == 'l')
			l++;
		else if (str[i] == 'h')
			l--;
		else
			return (-1);
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	if (str[i] == 'U')
		return (OptUnsignedLongLongInt);
	if (str[i] == 'D')
		return (OptLongLongInt);
	return (ft_spe_base(&str[i], l));
}

int			ft_spe_base(char *str, int l)
{
	int base;

	base = 0;
	if (*str == 'x' || *str == 'X')
		base = 16;
	if (*str == 'o' || *str == 'O')
		base = 8;
	if (*str == 'O')
		l = 2;
	if (*str == 'u' || *str == 'U')
		base = 20;
	if (*str == 'd' || *str == 'i' || *str == 'D')
		base = 10;
	if ((*str == 's' || *str == 'S') && l > 0)
		return (OptWString);
	if ((*str == 'c' || *str == 'c') && l > 0)
		return (OptWChar);
	if (base == 0)
		return (-1);
	return (10000 + 10 * base + l);
}

static int	ft_spe_type_suite(char c)
{
	if (c == 's')
		return (OptString);
	else if (c == 'S')
		return (OptWString);
	else if (c == 'p')
		return (OptAddress);
	else
		return (-1);
}

int			ft_spe_type(char c)
{
	if (c == '%')
		return (OptVoid);
	if (c == 'd' || c == 'i')
		return (OptInt);
	if (c == 'c')
		return (OptChar);
	if (c == 'C')
		return (OptWChar);
	if (c == 'D')
		return (OptLongLongInt);
	if (c == 'U')
		return (OptUnsignedLongLongInt);
	else if (c == 'x' || c == 'X')
		return (10160);
	else if (c == 'u')
		return (OptUnsignedInt);
	else if (c == 'o')
		return (OptOctal);
	else if (c == 'O')
		return (10000 + 82);
	return (ft_spe_type_suite(c));
}

int			ft_spe(char *s)
{
	int		i;

	i = 0;
	while (s[i] && ft_isspec(s[i]) == 0 && ft_istype(s[i]) == 0)
		i++;
	if (ft_istype(s[i]) == 1)
		return (ft_spe_type(s[i]));
	return (ft_spe2(&s[i]));
}
