/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unicode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 01:48:23 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/18 04:56:17 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <locale.h>

/*
** avec des test j'ai obtenue 55295 pour la limite du char
** ATTENION A LA TAILLE DE S
** 0xxxxxxx
** 110xxxxx 10xxxxxx
**    5     +   6                    = 11
** 1110xxxx 10xxxxxx 10xxxxxx
**      4  +   6 +      6			=  16
** 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
**  	3   +   6   +  6      +  6  =  21
**	flag precision ignore d'apres different test avec la vrai fct
**	meme chose pour le flag ' ', '+' et '#'
*/

int		len_unicode_byte(wchar_t c)
{
	int		taille;
	int		t;

	t = ft_lenbase(c, 2);
	if ((c >= 0xd800 && c < 0xe000))
		return (-1);
	if (c > 2097151 || c < 0)
		return (-1);
	taille = (t > 16) ? 4 : 1;
	taille = (t > 11 && t <= 16) ? 3 : taille;
	taille = (t > 7 && t <= 11) ? 2 : taille;
	taille = (MB_CUR_MAX >= taille) ? taille : -1;
	if ((c <= 255 && MB_CUR_MAX == 1))
		return (1);
	return (taille);
}

int		ft_put_unicode_string(wchar_t *str, t_printf pr)
{
	int		i;
	int		j;
	int		res;
	char	s[BUFF_SIZE];

	if (str == NULL)
		return (ft_put_null_string(pr));
	i = -1;
	res = 0;
	while (str[++i] && res + 4 < BUFF_SIZE)
	{
		if ((j = ft_get_unichar(&s[res], str[i], len_unicode_byte(str[i]))) < 0)
			return (-1);
		else if (res + j > pr.precis && pr.precis > 0)
			break ;
		else
			res += j;
	}
	s[res] = '\0';
	res = ft_put_string(s, pr);
	if (str[i] && res + 4 >= BUFF_SIZE)
		return (res + (ft_put_unicode_string(&str[i], pr)));
	return (res);
}

int		ft_put_unicode(wchar_t c, t_printf pr, int t)
{
	char	*tab;

	if (t == -1)
		return (-1);
	if (pr.larg <= t)
		return (ft_put_unichar(c, t));
	else
	{
		if (!(tab = (char *)malloc(sizeof(char) * (pr.larg + 1))))
			exit(0);
		(pr.flag_2 == ZERO) ? ft_memset(tab, '0', pr.larg) :
		ft_memset(tab, ' ', pr.larg);
		if (pr.flag_2 == MOINS)
		{
			ft_put_unichar(c, t);
			write(1, tab, pr.larg - t);
		}
		else
		{
			write(1, tab, pr.larg - t);
			ft_put_unichar(c, t);
		}
		free(tab);
	}
	return (ft_max(pr.larg, t));
}

int		ft_get_unichar(char *tab, wchar_t c, int taille)
{
	int		i;

	if (taille == -1)
		return (-1);
	tab[0] = (taille == 1) ? c : '\0';
	if (taille == 1)
		return (1);
	tab[0] = 0xf0;
	tab[1] = (taille == 3) ? 0xe0 : 0x80;
	tab[2] = (taille == 2) ? 0xc0 : 0x80;
	tab[3] = 0x80;
	tab[3] += c & 0x3f;
	c = c >> 6;
	tab[2] += (taille != 2) ? c & 63 : c & 31;
	c = (taille != 2) ? c >> 6 : c >> 5;
	tab[1] += (taille != 3) ? c & 63 : c & 15;
	c = (taille != 3) ? c >> 6 : c >> 4;
	tab[0] += c & 7;
	i = -1;
	while (++i < 4)
		if (i < taille)
			tab[i] = tab[4 - taille + i];
		else
			tab[i] = '\0';
	return (taille);
}

int		ft_put_unichar(wchar_t c, int taille)
{
	unsigned char tab[4];

	if (taille == 1)
		return (write(1, &c, 1));
	if (taille == -1)
		return (-1);
	tab[0] = 240;
	tab[1] = (taille == 3) ? 224 : 128;
	tab[2] = (taille == 2) ? 192 : 128;
	tab[3] = 128;
	tab[3] += c & 63;
	c = c >> 6;
	tab[2] += (taille != 2) ? c & 63 : c & 31;
	c = (taille != 2) ? c >> 6 : c >> 5;
	tab[1] += (taille != 3) ? c & 63 : c & 15;
	c = (taille != 3) ? c >> 6 : c >> 4;
	tab[0] += c & 7;
	return (write(1, &tab[4 - taille], taille));
}
