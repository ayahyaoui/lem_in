/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 21:52:05 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 04:03:21 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_word(char const *s, char c)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		j++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (j);
}

static int		ft_split(char const *s, char c, int *tab, char **str)
{
	int l;
	int k;
	int i;
	int j;

	i = tab[0];
	j = tab[1];
	l = 0;
	while (s[i] == c)
		i++;
	while (s[i + l] && s[i + l] != c)
		l++;
	str[j] = (char *)malloc((l + 1) * sizeof(char));
	k = -1;
	while (++k < l)
		str[j][k] = s[i + k];
	str[j][k] = '\0';
	return (i + k);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		tab[2];
	int		nb;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s)
		return (0x0);
	nb = count_word(s, c);
	if (!(str = (char **)malloc((nb + 1) * sizeof(*str))))
		return (0x0);
	while (++j < nb)
	{
		tab[0] = i;
		tab[1] = j;
		i = ft_split(s, c, tab, str);
	}
	str[j] = 0x0;
	return (str);
}
