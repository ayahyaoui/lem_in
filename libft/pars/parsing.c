/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:09:50 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/18 03:00:13 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**		ft_parsing recupere:
**			_l une liste d'option contenant toute les fct necessaire
**			_str  une String contenant toute la chaine
**			_va : liste d'argument
**		va separe par rapport au % et va appele process param a chaque fois
**		(affiche tout ce qui n'est pas un specifiere)
*/

int		affiche_reste(char *str)
{
	ft_putstr(str);
	return (-1);
}

int		ft_parsingbis(t_option *cursor, char *str, va_list va, char *buff)
{
	int i;
	int j;
	int res;

	i = 0;
	res = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '%')
			buff[j++] = str[i++];
		if (str[i])
		{
			i++;
			write(1, buff, j);
			res += j;
			bzero(buff, j + 1);
			if ((j = ft_process_param(cursor, &str[i], va, &res)) < 0)
				return (-1);
			i += j;
			j = 0;
		}
	}
	write(1, buff, j);
	return (res + j);
}

int		ft_parsing(t_option *l, char *str, va_list va)
{
	int			res;
	char		*buff;

	res = 0;
	if (!(buff = ft_memalloc(ft_strlen(str) + 1)))
		exit(0);
	res = ft_parsingbis(l, str, va, buff);
	free(buff);
	return (res);
}
