/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:29:03 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/13 17:26:00 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			displaypath(t_graphe *g, int *tab)
{
	unsigned int node;

	node = g->end;
	ft_printf("depart = %d\narriver = %d\n",g->start, node);
	while (node != (unsigned int)g->start)
	{
		ft_printf("%d<-",node);
		node = tab[node];
	}
	ft_printf("%d\n", node);
	return (1);
}

int			displayallpath(t_graphe *g, t_tab ***t)
{
	int i;
	int j;
//	int k;


	i = -1;
	while (t[++i])
	{
		j = -1;
		ft_putstr("=======================================\n");
		ft_printf(" nb chemin en parrallele %d (normalement)\n", i + 1);
		if (t[0][0]->length == 2 && i)
			ft_printf("%d>%d\n", g->start, g->end);
		if (!t[i])
			return 1;
		while (t[i][++j])
		{
		//	ft_printf("%d fourmis vont passer par la\n", t[i][j]->nb_ant);
			//ft_printf("i = %d et j = %d",i, j);
			if (t[i][j]->length == 0)
				return 1;
			ft_print_inttab(t[i][j]->tab, t[i][j]->length, '>');
		}
		ft_putstr("=======================================\n");
		ft_putstr("\n\n\n");
	}
	return (1);
}
