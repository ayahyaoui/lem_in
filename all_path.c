/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:31:00 by anyahyao          #+#    #+#             */
/*   Updated: 2018/10/21 23:17:35 by anyahyao         ###   ########.fr       */
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

void		test_parcours_recursif(t_graphe *g, t_path *path, int node
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
				test_parcours_recursif(g, path, i, p);
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



t_fusion		*create_fusion(t_path *p, int max)
{
	t_fusion *fusion;
	int i;

	fusion = (t_fusion *)malloc(sizeof(t_fusion));
	fusion->nb_path = p->nb_path;
	fusion->altern = 1;
	fusion->fusion  = (t_breakdown **)malloc(sizeof(t_breakdown*) * (p->nb_path * 2));
	i = -1;
	while (++i < p->nb_path)
	{
		fusion->fusion[i] = (t_breakdown*)malloc(sizeof(t_breakdown));
		fusion->fusion[i]->value = p->path[i][VALUE];
		fusion->fusion[i]->cost = p->path[i][COST];
		fusion->fusion[i]->breakdown = malloc(sizeof(int) * max);
		fusion->fusion[i]->breakdown[0] = p->path[i][VALUE];
		fusion->fusion[i]->len = 1;
	}
	return (fusion);
}

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

int		*my_best_tab(t_graphe *g, t_path *p, int lenMax)
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

void		affiche_path(t_path *p)
{
	int i;

	for (i = 0; i < p->nb_path; i++)
	{
		ft_printnbit((int)p->path[i][VALUE], 6);
		printf("==>%u = %u\n", p->path[i][VALUE], p->path[i][COST]);
	}
}

void		test_init_all_path(t_graphe *g, int end)
{
	t_path	*p;
	int		i;

	if (!g || g->taille > 32)
	{
		ft_printf("graphe trop grand pour les test\n");
		exit(1);
	}
	p = malloc(sizeof(t_path));
	p->nb_path = 0;
	g->end = end;
	test_parcours_recursif(g, p, 0, 0);
	printf("====il y'a %d chemins different==\n", p->nb_path);
	ft_tri_fusion_recursivecouple(p->path, p->nb_path);
	i = 0;
	if (0 < p->nb_path && p->path[0][COST] == 0)
	{
		p->path[i][VALUE] = 255;
		p->path[i][COST] = 8;
		i = 1;
	}
	affiche_path(p);
	my_best_tab(g, p, MIN(degre(g, 0) , degre(g, g->end)) - i);
	
	ft_printf("bien jouer\n");
	//	free(p->path);
	//free(p);
}

void		init_all_path(t_graphe *g)
{
	t_chemins	*chemins;
	int			degre;
	int			len;

	chemins = (t_chemins*)malloc(sizeof(chemins));
	degre = degre_graphe(g);
	len = (degre * g->taille / 8) + 1;
}

/*
   int main(int argc, const char *argv[])
   {
   char *test = malloc(5);
   test[0] = 'b';
   test[1] = 'c';
   test[2] = 'd';
   test[3] = '\0';
   test[4] = '\0';
   printf("%d, %d et %s\n",*test, test[1], test);
 *test = *test >> 8;
 printf("%d, %det %s\n",*test, test[1], test);
 free(test);
 return 0;
 }*/
