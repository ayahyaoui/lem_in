/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijistra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:53:09 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/16 23:22:34 by anyahyao         ###   ########.fr       */
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



t_tab	***dijkstra_loop(t_graphe *g)
{
	t_tab	***best_tab;
	int		max_separpath;
	max_separpath = MIN(degre(g, 0) , degre(g, g->end));
	if (!(best_tab = (t_tab***)malloc(sizeof(t_tab**) * (max_separpath + 1))))
		exit(3);
	best_tab[max_separpath] = 0x0;



	return (best_tab);
}
