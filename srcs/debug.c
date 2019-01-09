/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:29:03 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/09 13:17:39 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			displaypath(t_graphe *g, int *tab);
void		affiche_path(t_graphe *g, t_path *p);
void		printMultypath(int *res, int len);
int			displayallpath(t_graphe *g, t_tab ***t);
void	affichebreak(t_breakdown *bp);

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
			ft_printf("%8b\n", res[i + j]);
			ft_printf(" <%d> => %d\n", i + j, res[i+j]);
		}
		i+=j;
	}
}



void		affiche_path(t_graphe *g, t_path *p)
{
	unsigned int i;

	(void)g;
	for (i = 0; i < p->nb_path; i++)
	{
		ft_printf("%(g->taille - 1)b\n", (int)p->path[i][VALUE]);
//		ft_printnbit((int)p->path[i][VALUE], g->nb_rooms - 1);
		printf("==>%u = %u\n", p->path[i][VALUE], p->path[i][COST]);
	}
}

void	affichebreak(t_breakdown *bp)
{
	if (!bp)
	{
		ft_putstr("bp est NULL\n");
		return;
	}
	ft_printf("value = %d, cost = %d, et len = %d\n", bp->value, bp->cost, bp->len);
	ft_print_inttab((int*)bp->breakdown, bp->len,'/');

}

/*
 *	displaypath pas secur
 */

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

void		infos(t_fusion *f)
{
	int j;
	ft_putstr("                       fus\n");
	ft_printf("nombre de chemin <%u>, et nombre de voie en parallele (%u)\n",
			f->nb_path,f->altern);
	int i = -1;
	while ((unsigned int)++i < f->nb_path)
	{
		ft_printf("val = %u cout = %u et taille %u",
				f->fusion[i]->value, f->fusion[i]->cost, f->fusion[i]->len);
		j = -1;
		while ((unsigned int)++j < f->fusion[i]->len)
			ft_printf("(%d)", f->fusion[i]->breakdown[j]);
		ft_printf("\n");
	}
}


