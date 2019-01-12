/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   versionopti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:28:04 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/12 22:42:13 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define PATH_SIZE 16;

int			algoopti(t_graphe *g, ENV *e)
{
	t_tab		***besttab;
	int			res;

	g->nb_paths = 0;
	if (convert_graphe(g) == ERR_ALLOC || !(besttab = allowBestTab(50)))
		return (ERR_ALLOC);
	res = edmond_karp(g, besttab);
	if (res != NO_ERR)
		return (res);
	registerPath(g, g->nb_paths, besttab);
	g->nb_paths--;
	vielleSimulation(g, besttab, e->ins->nb_ants);
	e->all_paths = besttab;
	ft_printf("============================================================");
	ft_printf(" PREMIERE PARTIE FINIS ");
	ft_printf("============================================================\n");
	return (res);
}
/*
int			convert_map_to_graph(t_graphe *g)
{
	int room;
	int i;

	if (!(g->graph = creategraph(g->nb_rooms)))
			return (ERR_ALLOC);
	i = -1;
	while (++i < (int)g->nb_rooms)
	{
		j = -1;
		room = -1;
		while (++j < (int)g->nb_rooms)
			if (g->map[i][j] == 1)
				g->graph[i][++room] = j;
		g->graph[i][room + 1] = -1;
	}
}
*/

int			edmond_karp(t_graphe *g, t_tab ***besttab)
{
	int			i;
	t_node		*node;

	i = -42;
	while (42)
	{
		g->file = clean_file(g->file, g->nb_rooms);
		cleanNodee(g);
		ft_bzero(g->color, g->nb_rooms * 4);
		if (ajout_chemins(g) == -1)
			break ;
		i = g->node[g->end]->previous;
		node = g->node[i];
		if (is_break_path(g, i))
			if (!(registerPath(g, g->nb_paths, besttab)))
				return (ERR_ALLOC);
		while (node->value != g->start)
		{
			if (g->color[node->previous] == 0)
				node->parent = node->previous;
			node = g->node[node->previous];
		}
	}
	return ((i == -42) ? ERR_SOLUTION : NO_ERR);
}

int			ajout_chemins(t_graphe *g)
{
	t_node		*node;
	t_node		*suiv;
	int			i;

	node = g->node[g->start];
	node->color = BLACK;
	addfile(g->file, node->value);
	while (g->file->begin < g->file->end && (i = 0) == 0)
		if ((node = g->node[removefile(g->file)])->value == g->end)
			return (1);
		else if (node->parent != -1 && g->color[node->previous] == 0)
		{
			add_node_parcous(g, g->node[node->parent], node->value, 1);
		}
		else
			while (g->graph[node->value][i] != -1)
			{
				suiv = g->node[g->graph[node->value][i]];
				if (suiv->parent == -1 ||
					(suiv->parent >= 0 && suiv->parent != node->value))
					add_node_parcous(g, suiv, node->value, 0);
				i++;
			}
	return (-1);
}

void		add_node_parcous(t_graphe *g, t_node *next, int value, int opt)
{
	if (next->color == WHITE)
	{
		next->color = BLACK;
		next->previous = value;
		addfile(g->file, next->value);
		if (opt == 1)
			g->color[value] = 1;
	}
}

int			is_break_path(t_graphe *g, int start)
{
	t_node		*node;

	node = g->node[start];
	while (node->value != g->start)
	{
		if (g->color[node->previous] != 0)
			return (1);
		node = g->node[node->previous];
	}
	return (0);
}
