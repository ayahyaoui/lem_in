/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:29:03 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/16 04:58:25 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			displaypath(t_graphe *g, int *tab)
{
	unsigned int node;

	node = g->end;
//	ft_printf("depart = %d\narriver = %d\n",g->start, node);
	while (node != (unsigned int)g->start)
	{
		ft_printf("%d<-",node);
		node = tab[node];
	}
	ft_printf("%d\n", node);
	return (1);
}

void	infos_graphes(t_graphe *g)
{
	(void)g;
//	ft_printf("nb_rooms = %d, nb_tubes = %d\n", g->nb_rooms, g->nb_tubes);
//	ft_printf("start = %d, end = %d\n", g->start, g->end);

	/*ft_putstr("best paths:\n");
	  ft_print_inttab(g->capacite, g->nb_rooms, ' ');

	  ft_printf("map\n");
	  unsigned int i,j;
	  for (j = 0; j < g->nb_rooms; j++)
	  ft_printf("%2u ",j);
	  ft_putstr("\n");

	  for (i = 0; i < g->nb_rooms; i++) {
	  for (j = 0; j < g->nb_rooms; j++) {
	  ft_printf("%2d ",g->graph[j][i]);
	  }
	  ft_putstr("\n");
	  }*/
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
			ft_printf("%d>%d\n\n", g->start, g->end);
		if (!t[i])
			return 1;
		while (t[i][++j])
		{
		//	ft_printf("%d fourmis vont passer par la\n", t[i][j]->nb_ant);
			//ft_printf("i = %d et j = %d",i, j);
			if (t[i][j]->length == 0)
				return 1;
			ft_print_inttab(t[i][j]->tab, t[i][j]->length, '>');
			ft_putstr("\n");
		}
		ft_putstr("=======================================\n");
		ft_putstr("\n\n\n");
	}
	return (1);
}


void			printfile(t_file *f)
{
	int i;

	if (!f)
	{
		ft_putstr("GROS PB impossible file null printfile\n");
	}
	i = f->begin - 1;
	ft_printf("file %d-%d:", f->begin, f->end);
	while (++i < f->end - 1)
		ft_printf("%d ->", f->tab[i]);
	if (i < f->end)
		ft_printf("%d\n", f->tab[i]);
}



void	change_place_antbis(t_graphe *g, int *tab)
{
	int i;

	i = 0;
	while (++i < g->nb_paths && tab[i])
	;
	if (i == g->nb_paths && tab[i] == 0)
	{
		ft_printf("arrete d'appele cette fct");
		return;
	}
	tab[i] -= 1;
	tab[i - 1] += 1;
}


int			find_path_bonus(t_tab ***besttab, t_graphe *g)
{
	int i;
	int j;
	int k;
	int isin_path;

	i = -1;
	while (++i < g->nb_paths)
	{
		j = -1;
		while (besttab[i][++j])
		{
			isin_path = 0;
			k = -1;
			while (besttab[g->nb_paths][++k] && isin_path == 0)
			{
				if (besttab[g->nb_paths][k]->tab[1] == besttab[i][j]->tab[1])
					isin_path++;
			}
		}
	}
	return (1);
}


