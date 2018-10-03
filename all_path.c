/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:31:00 by anyahyao          #+#    #+#             */
/*   Updated: 2018/10/03 17:27:55 by anyahyao         ###   ########.fr       */
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
void		test_parcours_recursif(t_graphe *g, t_path *path, int node
		, unsigned long long p)
{
	int i;

	//printf(" mon chemins%llu\n", p);
	if (node == g->end)
	{
		i = -1;
		while (++i < path->nb_path)
			if (path->path[i] == p)
				return;
		path->path[path->nb_path] = p;
		path->nb_path = path->nb_path + 1;
		return ;
	}
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
	p->path = ft_memalloc(sizeof(long long) * degre_graphe(g) * g->taille);
	g->end = end;
	test_parcours_recursif(g, p, 0, 0);
	printf("il y'a %d chemins different\n", p->nb_path);
/*	for (i = 0; i < p->nb_path; i++)
	{
		ft_printnbit((int)p->path[i], 6);
		printf("\n");
	}
*/	free(p->path);
	free(p);
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
