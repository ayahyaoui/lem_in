/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:59:54 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:55:12 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**fill_tab(char **tab, char *str, size_t nb_words, int c)
{
	size_t	i;
	size_t	j;
	size_t	nb_chars;

	i = 0;
	while (*str && i < nb_words)
	{
		nb_chars = 0;
		while (*str == c)
			str++;
		while (*(str + nb_chars) && *(str + nb_chars) != c)
		{
			nb_chars++;
		}
		tab[i] = ft_strnew(nb_chars);
		j = 0;
		while (nb_chars--)
		{
			tab[i][j] = *str++;
			++j;
		}
		i++;
	}
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	char	*s_cpy;
	char	**str;
	size_t	nb_words;

	if (!s)
		return (NULL);
	s_cpy = (char *)(unsigned long)s;
	nb_words = ft_nbwords(s_cpy, c, 0);
	if (!(str = (char **)malloc(sizeof(char*) * (nb_words + 1))))
		return (NULL);
	str[nb_words] = NULL;
	return (!nb_words ? str : fill_tab(str, s_cpy, nb_words, c));
}
