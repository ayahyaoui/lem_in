/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:31:00 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/02 18:53:59 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"



int		get_all_separpath(t_graphe *g, t_path *p);
t_tab	**addpaths(t_graphe *g, t_tab *paths, int nb_path);
t_tab	*addpath(t_graphe *g, int path);
int		*my_best_tab(t_graphe *g, t_path *p, int lenMax, t_tab **best_tab);
int		searchNpath(t_path *p, t_fusion *prev, t_fusion *next, int *res);

void		parcours_recursif();

/**
**	test pour tout les graphe dont le nombre de noeud est inerieure a 32
**
*/


/*
t_way	*convertpath_to_way(t_graphe *g, unsigned long p)
{
	t_way *way;
	int i;
	int len;
	int j;
	int node;

	len =  number_active_bit(p, g->taille);
	way = malloc(sizeof(t_way) * len);
	i = -1;

	while (++i < len)
	{
		j = -1;
	//	while (++j < g->)
	}
	return (way);
}
*/


int		searchNpath(t_path *p, t_fusion *prev, t_fusion *next, int *res)
{
	int i;
	int j;
	t_fusion *tmp;
	int min;
	int cost;

	min = 32; // 32 > au cout maximale
	i = -1;
	while (++i < p->nb_path)
	{
		j = -1;
		while (++j < prev->nb_path)
			if (!(p->path[i][VALUE] & prev->fusion[j]->value)
			&& (prev->altern > 1 || j > i) &&
			(!valueisinfusion(next,p->path[i][VALUE] + prev->fusion[j]->value)))
			{
				cost = (p->path[i][COST] + prev->fusion[j]->cost);
				if (min > cost)
					min = getfusionpath(prev->fusion[j], res,
					p->path[i][VALUE], cost);
				fusion_path(next, p->path[i], prev->fusion[j]);
			}
	}
	next->altern++;
	infos(next);
	return 1;
}

int		*my_best_tab(t_graphe *g, t_path *p, int lenMax, t_tab **best_tab)
{
	int			*res;
	int			*t;
	t_fusion	*fus;
	t_fusion	*fus2;

	res = (int*)ft_memalloc(sizeof(int) * (lenMax * (lenMax + 1) / 2));
	fus = create_fusion(p, lenMax);
	fus2 = create_fusion(p, lenMax);
	t = res + 1;
	*res = p->path[0][VALUE];
	infos(fus); // pour le test
	while (fus->altern < lenMax)
	{
		fus2->nb_path = 0;
		searchNpath(p, fus, fus2, t);
		ft_swapPointeur(&fus, &fus2);
		if (fus->nb_path == 0)
		{
			printf("ouou======\n\n");
			break;
		}
		else
			t += fus->altern;
	}
	//free_path(p);
	//free_patha
	printMultypath(res, lenMax);
	return (res);
}

static int goodneig(t_graphe *g, int node, int path)
{
	int i;

	i = -1;
	while (++i < g->taille)
		if (g->map[i][node] == 1 && path & (1 << i))
			return (i);
	ft_putstr("pb on a pas de voisin qui correspond au chemin decrit\n");
	exit(0);
}


t_tab	*addpath(t_graphe *g, int path)
{
	t_tab	*t;
	int		len;
	int		node;
	int		i;

	i = -1;
	if (!(t = (t_tab*)malloc(sizeof(t_tab))))
		exit(3);
	len = number_active_bit(path, sizeof(int) * 8) + 1;
	if (!(t->tab = (int *)ft_memalloc(sizeof(int) * len)))
		exit(3);
	t->length = len;

	while (++i < len - 1)
	{
		node = goodneig(g, g->begin, path);
		t->tab[i] = node;
	}
	t->tab[i] = g->end;
	return (t);
}
t_tab	**addpaths(t_graphe *g, t_tab *paths, int nb_path)
{
	t_tab	**t;
	int		i;

	i = -1;
	if (!(t = (t_tab**)malloc(sizeof(t_tab *) * (nb_path + 1))))
		exit(3);
	t[nb_path] = 0x0;
	while (++i < nb_path)
		t[i] = addpath(g, paths->tab[i]);
	return t;
}

int		get_all_separpath(t_graphe *g, t_path *p)
{/*
	int		max_separpath;
	t_tab	***best_tab;
	t_tab	**tmp;

	max_separpath = MIN(degre(g, 0) , degre(g, g->end));
	if (!(best_tab = (t_tab***)malloc(sizeof(t_tab**) * (max_separpath + 1))))
		exit(3);
	best_tab[max_separpath] = 0x0;
	tmp = best_tab;
	if (p->nb_path > 0 && p->path[0][COST] == 0)
	{
		p->path[0][VALUE] = 255;
		p->path[0][COST] = 8;
		max_separpath--;
		best_tab[0] = addpath(g, 0);
	}
	affiche_path(p);
	my_best_tab(g, p, max_separpath, best_tab);
*/	return (1);
}


/*
void		init_all_path(t_graphe *g)
{
	t_chemins	*chemins;
	int			degre;
	int			len;

	chemins = (t_chemins*)malloc(sizeof(chemins));
	degre = degre_graphe(g);
	len = (degre * g->taille / 8) + 1;
}
*/
