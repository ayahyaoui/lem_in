/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 18:35:55 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/15 03:21:44 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_strcat_rev(const char *src, char *dst)
{
	char	*tmp;
	int		i;
	int		j;

	j = -1;
	i = ft_strlen(src);
	tmp = ft_strdup(dst);
	dst = ft_strcpy(dst, src);
	while (tmp[++j])
		dst[i++] = tmp[j];
	dst[i] = '\0';
	free(tmp);
	return (dst);
}

void	ft_put_string2(t_printf pr, int i, char *str)
{
	char	*tab;

	if (!(tab = (char *)malloc(sizeof(char) * (pr.larg))))
		exit(0);
	ft_memset(tab, ' ', i);
	tab[i] = 0;
	if (pr.flag_2 == ZERO)
		ft_memset(tab, '0', i);
	if (pr.flag_2 == MOINS)
		tab = ft_strcat_rev(str, tab);
	else
		tab = ft_strcat(tab, str);
	write(1, tab, pr.larg);
	free(tab);
}

int		ft_put_null_string(t_printf pr)
{
	char	*tab;
	int		t;
	int		sp;

	pr.precis = (pr.precis == -1 || pr.precis > 6) ? 6 : pr.precis;
	t = (pr.larg >= 0) ? pr.larg : 6;
	if (pr.precis > pr.larg)
		t = pr.precis;
	if (!(tab = ft_memalloc(t + 6)))
		exit(0);
	sp = (t > pr.precis) ? t - pr.precis : 0;
	if (pr.flag_2 == MOINS)
	{
		tab = ft_strncpy(tab, "(null)", pr.precis);
		ft_memset(&tab[t - sp], ' ', sp);
	}
	else
	{
		ft_memset(tab, ' ', sp);
		tab = ft_strncat(tab, "(null)", pr.precis);
	}
	write(1, tab, t);
	free(tab);
	return (t);
}

int		ft_put_string(const char *src, t_printf pr)
{
	int		taille;
	char	*str;

	if (src)
		str = ft_strdup(src);
	else
		return (ft_put_null_string(pr));
	taille = ft_strlen(str);
	if (pr.precis >= 0 && taille > pr.precis)
		taille = pr.precis;
	str[taille] = '\0';
	if (taille >= pr.larg)
		write(1, str, taille);
	else
		ft_put_string2(pr, pr.larg - taille, str);
	free(str);
	return ((pr.larg > taille) ? pr.larg : taille);
}
