/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repartAnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 21:58:25 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/15 23:50:28 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define ABS(X) (X > 0) ? X : -1 * X

#include "lem_in.h"


void		infos_graphes(t_graphe *g);
void		move(t_graphe *g, t_tab ***besttab);
void		add(t_graphe *g, int *tab, t_tab ***besttab);
int			isfinish(t_graphe *g, int *tab);
int			isfinishh(t_graphe *g, int *tab);
void		printAnt(t_graphe *g, int res, int *tab);
int			simulation(t_graphe *g, int *tab, t_tab ***besttab);
int			changeTab(int *tab);
void		addAnt(t_graphe *g, t_tab **besttab, int nbAnt);
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab);



/*
 *	c'est fonction n'est pas encore prete
 */

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

int			find_path_bonus(t_tab ***besttab, t_graphe *g)
{
	int i;
	int j;
	int k;
	int isin_path;

	i = -1;
	ft_printf("je vais faire un tessssssst\n");
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
			if (!isin_path)
				ft_print_inttab(besttab[i][j]->tab, besttab[i][j]->length, ' ');
		}
	}
	return (1);
}

int			place_ant(t_tab ***besttab, int fourmis, int path)
{
	int i;
	int j;
	int	nb_chemin;
	int pass;

	nb_chemin = 0;
	while (besttab[path][nb_chemin])
		nb_chemin++;
	i = nb_chemin;
	while (fourmis > 0)
	{
		pass = 0;
		j = -1;
		while (++j < nb_chemin)
			if (i >= besttab[path][j]->length)
			{
				pass++;
				besttab[path][j]->tab[0]++;
			}
		fourmis -= pass;
		i++;
	}
	return (i);
}


void	swap_pointeur(void **a, void **b)
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

void	change_place_ant(t_graphe *g, int *tab)
{
	int i;

	i = -1;
	while (++i < g->nb_paths && tab[i] == 0)
		;
	if (i > 0)
	{
		ft_printf("i = %d, tab[i] = %d\n", i, tab[i]);
		tab[i - 1] = tab[i];
		tab[i] = 0;
	}
}

int		prediction(ENV *e, t_graphe *g)
{
	int *best_combinaison;
	int *last_combinaison;
	int cost_best;
	int test = g->nb_paths;
	int test2 = 0;

	ft_bzero(g->color, sizeof(int) * g->nb_rooms);
	ft_bzero(g->previous, sizeof(int) * g->nb_rooms);
	best_combinaison = g->color;
	last_combinaison = g->previous;
	last_combinaison[g->nb_paths -1] = e->ins->nb_ants;
	best_combinaison[g->nb_paths -1] = e->ins->nb_ants;
	//
	
	//try_to_place_ant(e->all_paths, last_combinaison);
	//
	cost_best = -1;
	while (last_combinaison[0] != e->ins->nb_ants)
	{
		ft_print_inttab(last_combinaison, g->nb_paths + 1, ' ');
		 try_to_place_ant(e->all_paths, last_combinaison);
		ft_printf("j'ai placer les fourmis\n");
		
		scan_allmoves(e, DISPLAY_OFF);
		//ft_printf("milllll\n");
		ft_printf("j'ai verifie combien de tour => %d\n", e->turns);
		if (e->turns > 0 && (e->turns < cost_best || cost_best == -1))
		{
			
			ft_printf("yesss %d", e->turns);
			cost_best = e->turns;
			test2 = test;
			swap_pointeur((void**)&last_combinaison, (void**)&best_combinaison);
			ft_printf("nouveau record on remplace last par best\n");
		}
		ft_print_inttab(last_combinaison, g->nb_paths + 1, ' ');
		change_place_ant(g, last_combinaison);
		ft_printf("j'ai changer la combinaisont\n");
		test--;
	}
	return (test2);
}


/*
 *	par du principe que la somme de tab_fourmis est egale au nombre de fourmis
 */
int		try_to_place_ant(t_tab ***besttab, int *tab_fourmis)
{
	int i;
	int tmpres = 0;

	clean_ant(besttab);
	i = -1;
	while (besttab[++i])
		if (tab_fourmis[i] > 0)
			tmpres = place_ant(besttab, tab_fourmis[i], i);
	return tmpres;
}

void		clean_ant(t_tab ***besttab)
{
	int i;
	int j;

	i = -1;
	while (besttab[++i])
	{
		j = -1;
		while (besttab[i][++j])
			besttab[i][j]->tab[0] = 0;
	}
}

/*
void	move(t_graphe *g, t_tab ***besttab)
{
	int i;
	int j;
	t_tab *t;
	int *tmp;

	ft_bzero(g->capacite, sizeof(int) * g->nb_rooms);
	//printAnt(g,0, g->capacite);
	i = -1;
	while (++i < ((int)g->nb_rooms))
		if (g->color[i] > 0)
		{
			j = -1;
			while (besttab[g->color[i] - 1][++j])
			{
				t = besttab[g->color[i] - 1][j];
				if (IsinIntTab(t->tab, t->length , i))
				{
					j = searchIntTab(t->tab, t->length, i);
					//	ft_print_inttab(t->tab, t->length, ' ');
					//ft_printf("je recherche %d dans le tab res = %d\n", i, j);
					break;
				}
			}
			j++;
			if (j == t->length - 1)
				fourmis ++;//ft_printf("une fourmis est arrive a destination");
			else if (g->capacite[t->tab[j]] == 0)
				g->capacite[t->tab[j]] = g->color[i];
			else if (g->capacite[i] == 0)
				g->capacite[i] = g->color[i];
			else
				ft_printf("une fourmis vient de disparaitre en %d\n", i);
		}
	tmp = g->color;
	g->color = g->capacite;
	g->capacite = tmp;
	//ft_printf("move terminer\n");
	//printAnt(g, 0, g->capacite);
}



void		add(t_graphe *g, int *tab, t_tab ***besttab)
{
	int i;
	int j;

	i = (int)(g->nb_rooms);
	while (i > 0 && tab[i] <= 0)
		i--;
	j = -1;
//	ft_printf(" add est appele, i = %d\n", i);
	if (i == 0 && tab[0] == 0)
		return;
	while (besttab[i][++j])
	{
		//ft_printf("val = %d ", besttab[i][j]->tab[1]);
		if (tab[i] > 0 && g->color[besttab[i][j]->tab[1]] == 0)
		{
			//	ft_printf("yes");
			g->color[besttab[i][j]->tab[1]] = i + 1;
			tab[i]--;
		}
	}
}

int			isfinish(t_graphe *g, int *tab)
{
	int i;

	i = -1;
	ft_printf("nb rooms = %d\n", g->nb_rooms);
	while (++i < (int)(g->nb_rooms))
	{
		ft_printf("i = %d nb rooms = %d\n", i, g->nb_rooms);
		if (tab[i] > 0 || (i != g->end && g->color[i] != 0))
			return (0);
	}
	return (1);
}
int			isfinishh(t_graphe *g, int *tab)
{
	int i;

	i = -1;
	while (++i < (int)(g->nb_rooms))
	{
		if (tab[i] > 0 || (i != g->end && g->color[i] != 0))
		{
			ft_printf("probleme en %d",i);
			return (0);
		}
	}
	return (1);
}

void	printAnt(t_graphe *g, int res, int *tab)
{
	ft_printf("Tour numero %d \n", res);
	ft_print_inttab(g->color, (int)g->nb_rooms, ' ');
	ft_print_inttab(tab, g->nb_rooms, ' ');

}

int			simulation(t_graphe *g, int *tab, t_tab ***besttab)
{
	int res;
	ft_bzero(g->color, sizeof(int) * g->nb_rooms);
	ft_bzero(g->capacite, sizeof(int) * g->nb_rooms);
	//displayallpath(g, besttab);


	res = 0;
	//printAnt(g, res, tab);
	while (1)
	{
		//ft_printf("nouveau tour (%d)", res);
		move(g, besttab);
		add(g, tab, besttab);
		if (isfinish(g, tab))
			break;
		res++;
	}
	//ft_print_inttab(tab, g->nb_rooms, ' ');
	//printAnt(g, res, tab);
	//isfinishh(g, tab);
	infos_graphes(g);
	return res;

}
*/
/*
 *	a faire
 */
/*
int changeTab(int *tab)
{
	(void)tab;
	return (1);
}


int		searchIntTab(int *tab, int len, int value)
{
	int i;

	i = -1;
	while (++i < len)
		if (value == tab[i])
			return (i);
	return (-1);
}

int		IsinIntTab(int *tab, int len, int value)
{
	int i;

	i = -1;
	while (++i < len)
	{
		if (value == tab[i])
			return (1);
	}
	return (0);
}

*/
/*
 *	par du principe que besttab est triee
 */
/*
void		addAnt(t_graphe *g, t_tab **besttab, int nbAnt)
{
	int i;
	int j;
	int k;
	(void)g;
	i = -1;

	//displayallpath(besttab);
	ft_printf("il y'a %d foumis a placer\n", nbAnt);
	while (besttab[++i + 1] && nbAnt > 0)
	{
		//ft_printf("debut : %d %d\n", nbAnt/(i+1), besttab[i + 1]->length);
		if ((nbAnt / (i + 1)) > (besttab[i + 1]->length - besttab[i]->length))
		{
			k = besttab[i + 1]->length - besttab[i]->length;
			//	ft_printf("%d] k = %d \n", i, k);
			j = i + 1;
			while (--j >= 0)
			{
				nbAnt -= k;
				besttab[j]->tab[0] += k;
			}
		}
		else
		{
			//	ft_printf("%d} ", i);
			j = -1;
			while (++j <= i && nbAnt > 0)
			{
				nbAnt--;
				//		ft_printf("%d)\n", j);
				besttab[j]->tab[0] = besttab[j]->tab[0] + 1;
			}
		}
	}
	i++;
	j = -1;
	ft_printf("il reste %d fourmis a placer\n", nbAnt);
	k = nbAnt / i;
	while (++ j < i)
	{
		besttab[j]->tab[0] += k;
		if (j < nbAnt % i)
			besttab[j]->tab[0]++;
	}
}



*/
/*
void		bestsimulation(t_graphe *g, t_input *infos, t_tab ***besttab)
{
	int *tab = ft_memalloc(sizeof(int) *g->nb_rooms);
//	int min = 2000000000;
	//int calcul;
//	int i;
	tab[g->nb_paths] = infos->nb_ants;
	int *t = ft_memalloc(sizeof(int) *g->nb_rooms);
	t[g->nb_paths] = infos->nb_ants;
	displayallpath(g, besttab);
	ft_printf("on verifie %d\n", g->nb_paths - 1);
	//while (changeTab(tab) && min == 2000000000)
	//{
		//calcul = simulation(g, tab, besttab);
	//	if (calcul < min)
	//	{
	//		min = 18;
					//}
	//	}
	//}
	vielleSimulation(g, besttab, infos->nb_ants);
	//int test = test_simulation()
	ft_printf("resultat == rien");
	displayallpath(g, besttab);
	free(tab);
	free(t);
}
*/

