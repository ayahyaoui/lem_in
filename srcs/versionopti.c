/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   versionopti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 16:28:04 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/14 21:04:24 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int			algoopti(t_graphe *g, ENV *e)
{
	t_tab		***besttab;
	int			res;

	g->nb_paths = 0;
	if (convert_graphe(g) == ERR_ALLOC || !(besttab = allowBestTab(PATH_SIZE)))
		return (ERR_ALLOC);
	res = edmond_karp(g, &besttab);
	if (res != NO_ERR && !(res == ERR_SOLUTION && g->start_next_to_end))
		return (res);
//	ft_printf("dernier appele\n");
	if (!(besttab = registerPath(g, g->nb_paths, besttab)))
		return (ERR_ALLOC);
	g->nb_paths--;
	place_ant(besttab, e->ins->nb_ants, g->nb_paths);
//	ft_printf("============================================================");
//	ft_printf(" PREMIERE PARTIE FINIS ");
//	ft_printf("============================================================ %d\n", g->nb_paths);
	besttab[g->nb_paths + 1] = 0x0;
	//ft_printf("%d\n", besttab[0][0]->tab[0]);
	e->all_paths = besttab;
	return (res);
}

int			edmond_karp(t_graphe *g, t_tab ****besttab)
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
			if (!(*besttab = registerPath(g, g->nb_paths, *besttab)))
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
