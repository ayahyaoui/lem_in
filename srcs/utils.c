/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:34:11 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 06:31:03 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

t_list		*ft_lstval(t_list *l, int index)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = l;
	while (i < index)
	{
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}

/*
** ceci ne suis pas exactement le meme role que realloc
** elle permet de realloue lorsque que l'on connait le nombre de caractere
** que l'on veut garde (elle n'est pas securise on par du principe que
** t est > a la taille deja alloue)
*/

void		*ft_realloc(void *previous, size_t t, size_t len_src)
{
	unsigned char *dest;

	if (previous == 0x0 || t < len_src)
		return (0x0);
	if (!(dest = (unsigned char *)ft_memalloc(sizeof(char) * t)))
		return (0x0);
	dest = ft_memcpy(dest, previous, len_src);
	ft_memdel(&previous);
	return (dest);
}

void		swap_pointeur(void **a, void **b)
{
	char *c;
	char **aa;
	char **bb;

	aa = (char **)a;
	bb = (char **)b;
	c = *aa;
	*aa = *bb;
	*bb = c;
}
