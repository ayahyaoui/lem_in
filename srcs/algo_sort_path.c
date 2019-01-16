/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_sort_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:29:47 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/16 06:17:45 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		place_value_in_tab(int *tab, int value, int pos)
{
	int tmp;

	while (tab[pos] >= 0)
	{
		tmp = tab[pos];
		tab[pos] = value;
		value = tmp;
		pos++;
	}
	tab[pos] = value;
}

int				sort_path(t_graphe *g)
{
	int i;
	int j;

	ft_memset(g->previous, -1, sizeof(int) * g->nb_rooms);
	i = -1;
	while (++i < (int)g->nb_rooms)
	{
		if (g->capacite[i] > 0)
		{
			j = 0;
			while (g->previous[j] >= 0
					&& g->capacite[i] > g->capacite[g->previous[j]])
				j++;
			place_value_in_tab(g->previous, i, j);
		}
	}
	return (1);
}
