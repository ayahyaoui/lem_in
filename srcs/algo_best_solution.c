/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_best_solution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:35:36 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/16 23:10:28 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		add_node_parcours(t_graphe *g, t_node *next, int value, int opt)
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

static int		ajout_chemins(t_graphe *g)
{
	t_node		*node;
	t_node		*suiv;
	int			i;

	node = g->node[g->start];
	node->color = BLACK;
	addfile(g->file, node->value);
	while (!isemptyfile(g->file) && (i = 0) == 0)
		if ((node = g->node[removefile(g->file)])->value == g->end)
			return (1);
		else if (node->parent != -1 && g->color[node->previous] == 0)
			add_node_parcours(g, g->node[node->parent], node->value, 1);
		else
			while (g->graph[node->value][i] != -1)
			{
				suiv = g->node[g->graph[node->value][i]];
				if (suiv->parent == -1 ||
					(suiv->parent >= 0 && suiv->parent != node->value))
					add_node_parcours(g, suiv, node->value, 0);
				i++;
			}
	return (-1);
}

static int		is_break_path(t_graphe *g, int start)
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

static int		edmond_karp(t_graphe *g, t_tab ****besttab, int max_paths)
{
	int			i;
	t_node		*node;

	i = -42;
	while (max_paths--)
	{
		g->file = clean_file(g->file, g->nb_rooms);
		clean_node(g);
		ft_bzero(g->color, g->nb_rooms * sizeof(int));
		if (ajout_chemins(g) == -1)
			break ;
		i = g->node[g->end]->previous;
		node = g->node[i];
		if (is_break_path(g, i))
			if (!(*besttab = register_path(g, g->nb_paths, *besttab)))
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

int				find_best_solution(t_graphe *g, ENV *e)
{
	t_tab		***besttab;
	int			res;

	g->nb_paths = 0;
	if ((convert_graphe(g) == ERR_ALLOC)
		|| !(besttab = create_besttab(PATH_SIZE)))
		return (ERR_ALLOC);
	e->all_paths = besttab;
	res = edmond_karp(g, &besttab, e->max_paths);
	if (res != NO_ERR && !(res == ERR_SOLUTION && g->start_next_to_end))
		return (res);
	if (!(besttab = register_path(g, g->nb_paths, besttab)))
		return (ERR_ALLOC);
	g->nb_paths--;
	e->all_paths = besttab;
	try_to_place_ant(e->all_paths, prediction(e, e->graphe));
	scan_allmoves(e, DISPLAY_ON);
	return (NO_ERR);
}
