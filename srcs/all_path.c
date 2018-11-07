/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:31:00 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/07 16:28:03 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"



t_tab	***get_all_separpath(t_graphe *g, t_path *p);
t_tab	**addpaths(t_graphe *g, t_breakdown *paths, int nb_path);
t_tab	*addpath(t_graphe *g, int path);
int		*my_best_tab(t_graphe *g, t_path *p, unsigned int lenMax, t_tab ***best_tab);
//int		searchNpath(t_path *p, t_fusion *prev, t_fusion *next);

void		parcours_recursif(void);

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

	len =  number_active_bit(p, g->nb_rooms);
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


t_breakdown	*searchNpath(t_path *p, t_fusion *prev, t_fusion *next, t_tab **res)
{
	int i;
	int j;
	int min;
	int cost;
	t_breakdown  *b = 0x0;

	(void)res;
	min = 32; // 32 > au cout maximale
	i = -1;
	while ((unsigned int)++i < p->nb_path)
	{
		j = -1;
		while ((unsigned int)++j < prev->nb_path)
			if (!(p->path[i][VALUE] & prev->fusion[j]->value)
			&& (prev->altern > 1 || j > i) &&
			(!valueisinfusion(next,p->path[i][VALUE] + prev->fusion[j]->value)))
			{
				cost = (p->path[i][COST] + prev->fusion[j]->cost);
				fusion_path(next, p->path[i], prev->fusion[j]);
				if (min > cost)
				{
					min = cost;
					b = next->fusion[next->nb_path - 1];
	//min = getfusionpath(prev->fusion[j], res,p->path[i][VALUE], cost);
				}
			}
	}
	next->altern++;
	ft_printf("nouvelle conbinaison %d\n\n\n", next->altern);
	//infos(next);
	return b;
}

int		*my_best_tab(t_graphe *g, t_path *p, unsigned int lenMax, t_tab ***best_tab)
{
	int i = -1;
	t_fusion	*fus;
	t_fusion	*fus2;

	fus = create_fusion(p, lenMax);
	fus2 = create_fusion(p, lenMax);
	infos(fus); // pour le test
	//best_tab[0] = addpaths(g, , fus->altern + 1);
	while (fus->altern < lenMax)
	{
		fus2->nb_path = 0;
		ft_printf("=========%d=======\n", fus->altern);
		best_tab[fus->altern -1] = addpaths(g,
			searchNpath(p, fus, fus2, best_tab[i]), fus->altern + 1);
		ft_swapPointeur(&fus, &fus2);
		fus2->altern = fus->altern;
		ft_printf("nb_path = <<%d>>\n",fus->nb_path);
		if (fus->nb_path == 0)
		{
			printf("ouou======\n\n");
			break;
		}
	}
	ft_putstr("finit la premiere parti\n");
	free_fusion(fus);
	free_fusion(fus2);
	return (0x0);
}

static int goodneig(t_graphe *g, int *tab, int path, int pos)
{
	int i;
	int node;

	i = -1;
	node = tab[pos - 1];
	ft_printf("node = %d et chemin = %d\n", node, path);
	while ((unsigned int)++i < g->nb_rooms)
		if (g->map[i][node] == 1 && (path & (1 << i)) &&
			ft_isintab(tab, pos - 1, i) == 0)
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

	i = 0;
	(void)node;
	if (!(t = (t_tab*)malloc(sizeof(t_tab))))
		exit(3);
	len = number_active_bit(path, sizeof(int) * 8) + 2;
	if (!(t->tab = (int *)ft_memalloc(sizeof(int) * (len))))
		exit(3);
	t->length = len;
	t->tab[0] = g->start;
	while (++i < len - 1)
		t->tab[i] = goodneig(g, t->tab, path, i);
	t->tab[i] = g->end;
	return (t);
}

t_tab	**addpaths(t_graphe *g, t_breakdown *br, int nb_path)
{
	t_tab	**t;
	int		i;

	i = -1;
	ft_printf("OHOH %d\n", nb_path);
	affichebreak(br);
	if (!br)
		return (0x0);
	if (!(t = (t_tab**)malloc(sizeof(t_tab *) * (nb_path + 1))))
		exit(3);
	t[nb_path] = 0x0;
	while (++i < nb_path)
		t[i] = addpath(g, br->breakdown[i]);
	ft_printf("OHOHfini\n", nb_path);
	return t;
}

t_tab		***get_all_separpath(t_graphe *g, t_path *p)
{
	int		boolean = 0;
	int		max_separpath;
	t_tab	***best_tab;
	t_fusion	*fus;

	max_separpath = MIN(degre(g, 0) , degre(g, g->end));
	fus = create_fusion(p, max_separpath);
	if (!(best_tab = (t_tab***)malloc(sizeof(t_tab**) * (max_separpath + 1))))
		exit(3);
	best_tab[max_separpath] = 0x0;
	best_tab[0] = addpaths(g, fus->fusion[0], 1); // trouve un moyen paths
	if (p->nb_path > 0 && p->path[0][COST] == 0)
	{
		p->path[0][VALUE] = 255;
		p->path[0][COST] = 8;
		max_separpath--;
		fus->fusion[0]->value = 255;
		if (p->nb_path > 1)
		{
			boolean = 1;
			best_tab[1] = addpaths(g, fus->fusion[2], 1); // trouve un moyen paths
		}
		//best_tab[0] = addpath(g, 0);
	}
	free_fusion(fus);
	affiche_path(g, p);
	if (max_separpath > 0)
		my_best_tab(g, p, max_separpath, &best_tab[1 + boolean]);
	displayallpath(g, best_tab);
	//free_besttab(best_tab);
	return (best_tab);
}


/*
void		init_all_path(t_graphe *g)
{
	t_chemins	*chemins;
	int			degre;
	int			len;

	chemins = (t_chemins*)malloc(sizeof(chemins));
	degre = degre_graphe(g);
	len = (degre * g->nb_rooms / 8) + 1;
}
*/
