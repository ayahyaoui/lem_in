/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijistra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:53:09 by anyahyao          #+#    #+#             */
/*   Updated: 2018/12/09 17:27:56 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 *	on part du principe que le depart et arrive rechercher sont dans g->start
 *	et que path est deja allouer
 *	file et path doivent etre clean
 */
	//file = clean_file(file, g->nb_rooms);

int		addneighbour(t_graphe *g, int node, int *avoid)
{
	int i;

	i = -1;
	while ((unsigned int)++i < g->nb_rooms)
	{
		if (g->color[i] == WHITE && g->map[i][node] == 1 &&
				(!avoid || !avoid[i]))
		{
			g->color[i] = GREY;
			addfile(g->file, i);
			return (i);
		}
	}
	return (-1);
}

int		dijkstra(t_graphe *g, int *avoid, int *path)
{
	int			neigh;
	int			node;

	addfile(g->file, g->start);
	g->color[g->start] = GREY;
	while (!isemptyfile(g->file))
	{
		node = removefile(g->file);
		neigh = addneighbour(g, node, avoid);
		path[node] =  (neigh == -1) ? path[node] : neigh;
		if (neigh == g->end)
			return (1);
		g->color[node] = BLACK;
	}
	return (0);
}

/**
 *	lors de la prochaine verison on auras le choix entre pointe sur un autre
 *	chemin pour pas duplique ou cree si le chemin est different
 */
/*
static int	addpathintab(t_tab ***best_tab, int *path, int index)
{
	int i;

	i = -1;
	if (!(best_tab[index] = (t_tab**)malloc(sizeof(t_tab*))))
		exit(ERRORMALLOC);
	while (++i < index)
	{
		if (!(best_tab[index][i] = (t_tab*)malloc(sizeof(t_tab))) ||
		!(best_tab[index][i] = ft_memalloc(best_tab[index - 1][i]->length)))
					exit(ERRORMALLOC);
		best_tab[index][i] = ft_memcpy(best_tab[index][i],
				best_tab[index - 1][i]->tab, best_tab[index - 1][i]->);
	}
	if (!(best_tab[index][index] = (t_tab*)malloc(sizeof(t_tab))))
		exit(ERRORMALLOC);
	//while (path[])
	//{



	return (1);
}
*/
t_tab	***dijkstra_loop(t_graphe *g)
{
	t_tab	***best_tab;
	int		max_separpath;
	int		i;
	int		*avoid;
	int		*tmp;

	i = -1;
	max_separpath = MIN(degre(g, 0) , degre(g, g->end));
	if (!(best_tab = (t_tab***)malloc(sizeof(t_tab**) * (max_separpath + 1))))
		exit(3);
	best_tab[max_separpath] = 0x0;
	if (!(avoid = ft_memalloc(sizeof(int) * g->nb_rooms)))
		exit(1);
	if (!(tmp = ft_memalloc(sizeof(int) * g->nb_rooms)))
		exit(1);
	while (++i < max_separpath)
	{
		if (dijkstra(g, avoid, tmp) == 0)
		{
			best_tab[i] = 0x0;
			break;
		}
		//addpathintab(best_tab, path, i);
	}
	free(avoid);
	return (best_tab);
}
