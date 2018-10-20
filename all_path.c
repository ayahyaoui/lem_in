/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:31:00 by anyahyao          #+#    #+#             */
/*   Updated: 2018/10/21 00:52:25 by anyahyao         ###   ########.fr       */
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



t_fusion		*create_fusion(t_path *p)
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
		fusion->fusion[i]->breakdown = malloc(20); // juste pour le test
		fusion->fusion[i]->len = 0;
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
	t_breakdown *src;
	int i;

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


int		getfusionpath(t_fusion *fusion, int *res)
{
	int		i;
	t_breakdown *b;

	i = -1;
	b = fusion->fusion[fusion->nb_path];
	while (++i < b->len)
		res[i] = b->breakdown[i];
	return (1);
}

void		infos(t_fusion *f)
{
	ft_putstr("fus\n");
	ft_printf("f->nb_path = %u, et nombre en parallele %u\n", f->nb_path,f->altern);
	int i = -1;
	while (++i < f->nb_path)
		ft_printf("val = %u cout = %u et taille %u\n",
				f->fusion[i]->value, f->fusion[i]->cost, f->fusion[i]->len);

}


int		searchNpath(t_path *p, t_fusion *prev, t_fusion *next, int *res)
{
	int i;
	int j;
	t_fusion *tmp;
	int min;

	min = -1;
	i = -1;
	while (++i < p->nb_path)
	{
		j = -1;
		while (++j < prev->nb_path)
			if (!(p->path[i][VALUE] & prev->fusion[j]->value))
				if (prev->altern > 1 || j > i)
				{
					ft_printf("%u et %u\n",p->path[i][VALUE] , prev->fusion[j]->value);
					fusion_path(next, p->path[i], prev->fusion[j]);
					//if (min == -1 || min > (p->path[i][COST] + prev->fusion[j]->cost))
					//	getfusionpath(next, res);
				}
	}
	infos(prev);
	infos(next);
	next->altern++;
	return 1;
}

/*
 * considere p non vide (au moins 2 chemins trouve)
 */
int		*my_best_tab(t_graphe *g, t_path *p, int lenMax)
{
	int			*res;
	int			*t;
	t_fusion	*fus;
	t_fusion	*fus2;

	ft_printf("debut, %d\n", lenMax);
	res = (int*)malloc(sizeof(int) * (lenMax * (lenMax + 1) / 2));
	fus = create_fusion(p);
	fus2 = create_fusion(p);
	t = res + 1;
	*res = p->path[0][VALUE];
//	infos(fus);
//	infos(fus2);
	while (fus->altern < lenMax)
	{
		fus2->nb_path = 0;
		searchNpath(p, fus, fus2, t);
		ft_swapPointeur(&fus, &fus2);
		if (fus->nb_path == 0)
			break;
		else
			t += fus->altern;
	}
	//free_path(p);
	//free_path
	return (res);
}

/*
int			countmaxCombination(int len, int fusion)
{
	if (fusion == 1)
		return (len);
	else if (fusion < 1)
		exit(printf("Gros pb combination\n"));
	else
		return (countmaxCombination( , fusion - 1));

*/
void		affiche_path(t_path *p)
{
	int i;

	for (i = 0; i < p->nb_path; i++)
	{
		ft_printnbit((int)p->path[i][VALUE], 6);
		printf("==>%d\n", p->path[i][VALUE]);
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
	// p->path = ft_tri_fusion_recursivecouple(p->path, p->nb_path);
	printf("il y'a %d chemins different\n", p->nb_path);
	affiche_path(p);
	my_best_tab(g, p, MIN(degre(g, 0), degre(g, g->end)));
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
