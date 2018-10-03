/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 01:38:28 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/18 03:02:05 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
**		ft_process_param recupere:
**			_cursor : une liste contenant touts les fct necessaire
**			_str : un String contenant toute les info de % -> la fin
**			_va : liste d'arguement
**			res : nombre de caractere ecris
**		va traduire les information de str en t_printf et spe (specificateur)
**		puis trouve et appelle la fonction necessaire dans cursor correspondant
**		au specificateur
*/

int		ft_process_parambase(t_option *cursor, va_list va, t_printf pr, int spe)
{
	long long	len;
	int			l;

	spe -= 10000;
	len = 0;
	len = (spe % 10 == 8) ? (char)va_arg(va, int) : len;
	len = (spe % 10 == 9) ? (short)va_arg(va, int) : len;
	len = (spe % 10 == 0) ? va_arg(va, int) : len;
	len = (spe % 10 == 1) ? va_arg(va, long) : len;
	len = (spe % 10 == 2) ? va_arg(va, long long) : len;
	l = (spe % 10 >= 8) ? ((spe % 10) - 10) : (spe % 10);
	spe = (spe % 10 >= 8) ? (spe + 2) / 10 : spe / 10;
	if (l > 2 || l < -2)
		undefined("ft_process_parambase", -1, "basepb", "pb");
	if (spe == 10)
		return (cursor->fct.opt_long_long_int(len, pr));
	if (l > 0)
		l = (l == 1) ? (sizeof(long)) : (sizeof(long long));
	else if (l < 0)
		l = (l == -1) ? (sizeof(short)) : (sizeof(char));
	l = (l == 0) ? (sizeof(int)) : l;
	return (cursor->fct.opt_base(len, pr, l, spe));
}

int		ft_process_unsigned(t_option *cursor, va_list va, t_printf pr, int spe)
{
	unsigned long long	len;

	spe -= 10000;
	len = 0;
	len = (spe % 10 == 8) ? (unsigned char)va_arg(va, int) : len;
	len = (spe % 10 == 9) ? (unsigned short)va_arg(va, int) : len;
	len = (spe % 10 == 0) ? va_arg(va, unsigned int) : len;
	len = (spe % 10 == 1) ? va_arg(va, unsigned long) : len;
	len = (spe % 10 == 2) ? va_arg(va, long long) : len;
	spe = (spe % 10 >= 8) ? (spe + 2) / 10 : spe / 10;
	return (cursor->fct.opt_unsigned_long_long_int(len, pr));
}

int		ft_process_param3(t_option *cursor, va_list va, t_printf pr, int spe)
{
	wchar_t w;

	if (cursor == NULL)
		undefined("ft_process_param3", -1, "le pb est avant", " cursor null");
	if (spe >= 10000 && spe <= 10162)
		return (ft_process_parambase(cursor, va, pr, spe));
	if (spe >= 10198 && spe <= 10202)
		return (ft_process_unsigned(cursor, va, pr, spe));
	if (spe == OptVoid)
		return (cursor->fct.opt_void(pr));
	if (spe == OptChar)
		return (cursor->fct.opt_w_char((char)va_arg(va, int), pr, 1));
	if (spe == OptWChar)
	{
		w = va_arg(va, wchar_t);
		return (cursor->fct.opt_w_char(w, pr, len_unicode_byte(w)));
	}
	if (spe == OptString)
		return (cursor->fct.opt_str(va_arg(va, char *), pr));
	if (spe == OptWString)
		return (cursor->fct.opt_w_str(va_arg(va, wchar_t *), pr));
	if (spe == OptAddress)
		return (cursor->fct.opt_address(va_arg(va, void *), pr));
	return (0);
}

int		ft_process_param(t_option *cursor, char *str, va_list va, int *res)
{
	int			i;
	t_printf	pr;
	int			spe;
	char		*key;
	int			r;

	if (ft_secure(str) == -1)
		return (0);
	spe = ft_spe(str);
	if (spe == -1)
		return (-1);
	key = get_key(spe);
	i = 0;
	pr = init_pr();
	pr = get_flag(pr, str);
	while (cursor != NULL && ft_strcmp(cursor->keyword, key))
		cursor = cursor->next;
	free(key);
	if (cursor == NULL)
		exit(0);
	r = ft_process_param3(cursor, va, pr, spe);
	*res = (r == -1) ? -1 : *res + r;
	while (str[i] && ft_istype(str[i]) == 0)
		i++;
	return ((*res == -1) ? -1 : (i + 1));
}
