/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:31:00 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/01 22:05:38 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"




void		parcours_recursif();
int			degre_graphe(t_graphe *g)
{
	int i;
	int res;
	int j;

	if (g == 0X0)
		return (-1);
	i = -1;
	res = 0;
	while (++i < g->taille)
	{
		j = -1;
		while (++j < g->taille)
			if(g->map[i][j])
				res++;
	}
	return (res / 2);
}

/**
**	test pour tout les graphe dont le nombre de noeud est inerieure a 32
**
*/

int		number_active_bit(unsigned long p, int max);

void		getallpath(t_graphe *g, t_path *path, int node
		, unsigned int p)
{
	int i;

	if (node == g->end)
	{
		i = -1;
		while (++i < path->nb_path)
			if (path->path[i][0] == p)
				return;
		path->path[path->nb_path][VALUE] = p;
		path->path[path->nb_path][NBNODE] = number_active_bit(p, 32);
		path->nb_path = path->nb_path + 1;
		return ;
	}
	if (node == 0 && p != 0)
		return;
	if (node != 0)
		p += (1 << node);
	i = -1;
	while (++i < g->taille)
	{
		if (g->map[node][i])
		{
			if (!(p & (1 << i)))
				getallpath(g, path, i, p);
		}
	}
	g->color[node] = BLACK;
}

/*
**	renvois le nombre de voisin d'un noeud
*/

int			degre(t_graphe *g, int node)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (++i < g->taille)
		if (g->map[node][i])
			res++;
	return (res);
}


/*
** renvois le nombre de bit actif (soit le nombre de noeud sur un chemins)
*/

int		number_active_bit(unsigned long p, int max)
{
	int i;
	int res;

	res = 0;
	i = -1;
	while (++i < max)
		if (p & 1 << i)
			res++;
	return (res);
}

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


void	ft_swapPointeur(t_fusion **a, t_fusion **b)
{
	t_fusion *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		fusion_path(t_fusion *fusion, unsigned int tab[2], t_breakdown *copy)
{
	t_breakdown	*src;
	int			i;

	i = -1;
	src = fusion->fusion[fusion->nb_path];
	src->value = tab[VALUE] + copy->value;
	src->cost = tab[COST] + copy->cost;
	src->len = copy->len + 1;
	while (++i < copy->len)
		src->breakdown[i] = copy->breakdown[i];
	src->breakdown[copy->len] = tab[VALUE];
	fusion->nb_path++;
	return (1);
}


int		getfusionpath(t_breakdown *b, int *res, unsigned int val, int cost)
{
	int		i;

	i = -1;
	//ft_printf("//%d et %d", b->value, val);
	while (++i < b->len)
	{
		//ft_printf("getfusionpath  %d",b->breakdown[i]);
		res[i] = b->breakdown[i];
	}
		res[i] = val;
	return (cost);
}

void		infos(t_fusion *f)
{
	int j;
	ft_putstr("                       fus\n");
	ft_printf("nombre de chemin <%u>, et nombre de voie en parallele (%u)\n",
			f->nb_path,f->altern);
	int i = -1;
	while (++i < f->nb_path)
	{
		ft_printf("val = %u cout = %u et taille %u",
				f->fusion[i]->value, f->fusion[i]->cost, f->fusion[i]->len);
		j = -1;
		while (++j < f->fusion[i]->len)
			ft_printf("(%d)", f->fusion[i]->breakdown[j]);
		ft_printf("\n");
	}
}

int			valueisinfusion(t_fusion *fusion, int value)
{
	int i;
	i = -1;
	if (!fusion)
		return (0);
	while (++i < fusion->nb_path)
		if (value == fusion->fusion[i]->value)
			return (1);
	return (0);
}

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

int		get_all_separpath(t_graphe *g, t_path *p)
{
	int		max_separpath;
	t_tab	**best_tab;
	t_tab	**tmp;

	max_separpath = MIN(degre(g, 0) , degre(g, g->end));
	if (!(best_tab = (t_tab**)malloc(sizeof(t_tab*) * max_separpath)))
		exit(3);
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
	return (1);
}


void		test_multipathbinary(t_graphe *g)
{
	t_path	*p;
	int		i;

	ft_printf("debut MULTI PATH\n");
	if (!g || g->taille > 32)
	{
		ft_printf("graphe trop grand pour les test\n");
		exit(1);
	}
	if (!(p = malloc(sizeof(t_path))))
			exit(3);
	p->nb_path = 0;
	getallpath(g, p, 0, 0);
	printf("====il y'a %d chemins different==\n", p->nb_path);
	ft_tri_fusion_recursivecouple(p->path, p->nb_path);
	i = 0;
	get_all_separpath(g, p);

	ft_printf("bien jouer\n");
	//	free(p->path);
	//free(p);
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
}*/
