/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_register_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:46:18 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/16 19:25:11 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int		add_path(t_node *node, t_graphe *g, t_tab *t)
{
	int pos;

	if (node->value == g->start)
	{
		t->tab[0] = g->start;
		return (1);
	}
	pos = add_path(g->node[node->parent], g, t);
	t->tab[pos] = node->value;
	return (pos + 1);
}

static void		get_infos_allocate_tab(t_graphe *g, int *nb_path, int *size_max)
{
	int			i;
	t_node		*node;

	ft_bzero(g->capacite, sizeof(int) * g->nb_rooms);
	i = -1;
	*nb_path = (g->start_next_to_end == 1) ? 1 : 0;
	*size_max = (g->start_next_to_end == 1) ? 2 : -1;
	while (++i < (int)g->nb_rooms)
	{
		if (g->map[i][g->end] > 0 && g->node[i]->parent >= 0)
		{
			node = g->node[i];
			g->capacite[i] += 1;
			while (node->value != g->start)
			{
				node = g->node[node->parent];
				g->capacite[i] += 1;
			}
			if (g->capacite[i] > *size_max)
				*size_max = g->capacite[i];
			*nb_path = *nb_path + 1;
		}
	}
}

static t_tab	**allocate_tab(t_graphe *g, t_tab **besttab)
{
	int i;
	int j;
	int size_max;

	j = 0;
	get_infos_allocate_tab(g, &j, &size_max);
	if (!(besttab = ft_memalloc(sizeof(t_tab *) * (j + 2))))
		return (0x0);
	i = -1;
	while (++i < j)
	{
		if (!(besttab[i] = (t_tab*)ft_memalloc(sizeof(t_tab))))
			return (0x0);
		if (!(besttab[i]->tab = ft_memalloc(sizeof(int) * (size_max + 2))))
			return (0x0);
	}
	besttab[j] = 0x0;
	return (besttab);
}

static void		ft_add_exeption(t_graphe *g, t_tab ***besttab, int nb_path)
{
	if (g->start_next_to_end)
	{
		besttab[nb_path][0]->length = 2;
		besttab[nb_path][0]->tab[1] = g->end;
	}
}

t_tab			***register_path(t_graphe *g, int nb_path, t_tab ***tab)
{
	int i;
	int k;

	if (nb_path > 0 && (nb_path % PATH_SIZE) == 0)
		if (!(tab = (t_tab***)ft_realloc((char*)tab,
			sizeof(t_tab**) * (nb_path + PATH_SIZE + 1),
			sizeof(t_tab **) * (nb_path))))
			return (0x0);
	if (!(tab[nb_path] = allocate_tab(g, tab[nb_path])))
		return (0x0);
	i = 0;
	sort_path(g);
	k = g->start_next_to_end;
	ft_add_exeption(g, tab, nb_path);
	while (g->previous[i] >= 0)
	{
		tab[nb_path][i + k]->length =
			add_path(g->node[g->previous[i]], g, tab[nb_path][i + k]) + 1;
		tab[nb_path][i + k]->tab[tab[nb_path][i + k]->length - 1] = g->end;
		++i;
	}
	g->nb_paths++;
	return (tab);
}
