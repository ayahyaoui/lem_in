/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 19:19:08 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/18 01:56:41 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	undefined(char *where, int i, char *ou, char *msg)
{
	ft_printf("probleme dans la fonction %s\n", where);
	if (i > 0 || i > (int)ft_strlen(ou))
		ft_printf("cause %s sur %s precisement(%c)\n", msg, ou, ou[i]);
	else
		ft_printf("cause %s sur %s \n", msg, ou);
	ft_printf("merci d'avoir utiliser ft_printf\n");
}

int		ft_printf(const char *str, ...)
{
	va_list		va;
	t_option	*opt;
	t_option	*cl;
	int			res;

	opt = initialisation_liste_opt();
	va_start(va, str);
	cl = opt;
	res = ft_parsing(opt, (char*)str, va);
	va_end(va);
	ft_clean_option(cl);
	return (res);
}
