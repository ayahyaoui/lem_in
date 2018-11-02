/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:29:03 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/02 18:54:00 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			displaypath(t_graphe *g, int *tab);
void		affiche_path(t_path *p);
void		printMultypath(int *res, int len);

/*
 ** considere p non vide (au moins 2 chemins trouve)
 */

void		printMultypath(int *res, int len)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	len = len * (len + 1) / 2;
	while (i < len)
	{
		k++;
		j = -1;
		ft_printf("plus petit ensemble de chemin taille <%d>\n", i + 1 );
		while (++j < k)
		{
			if (res[i +j] == 0)
			{
				i = len + 1;
				break;
			}
			ft_printnbit(res[i + j], 8);
			ft_printf(" <%d> => %d\n", i + j, res[i+j]);
		}
		i+=j;
	}
}



void		affiche_path(t_path *p)
{
	int i;

	for (i = 0; i < p->nb_path; i++)
	{
		ft_printnbit((int)p->path[i][VALUE], 6);
		printf("==>%u = %u\n", p->path[i][VALUE], p->path[i][COST]);
	}
}

/*
 *	displaypath pas secur
 */

int			displaypath(t_graphe *g, int *tab)
{
	int node;

	node = g->end;
	ft_printf("depart = %d\narriver = %d\n",g->begin, node);
	while (node != g->begin)
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
	int k;


	i = -1;
	while (t[++i])
	{
		j = -1;
		ft_putstr("=======================================\n");
		ft_printf(" nb chemin en parrallele %d (normalement)\n", i + 1);
		while (t[i][++j])
		{
		//	ft_printf("%d fourmis vont passer par la\n", t[i][j]->nb_ant);
			ft_affichetab(t[i][j]->tab, t[i][j]->length, '>');
		}
		ft_putstr("=======================================\n");
		ft_putstr("\n\n\n");
	}
	return (1);
}
