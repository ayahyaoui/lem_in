/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:22:17 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/16 05:05:55 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_node(t_graphe *g)
{
	int i;

	if (g->node)
	{
		i = -1;
		while (++i < (int)g->nb_rooms)
			ft_memdel((void**)&g->node[i]);
		ft_memdel((void **)&g->node);
	}
}

void			free_graphe(t_graphe *g)
{
	int i;

	i = -1;
	if (!g)
		return ;
	if (g->map)
	{
		while ((unsigned int)++i < g->nb_rooms)
			ft_memdel((void **)&g->map[i]);
		ft_memdel((void **)&g->map);
	}
	i = -1;
	if (g->graph)
	{
		while ((unsigned int)++i < g->nb_rooms)
			ft_memdel((void **)&g->graph[i]);
		ft_memdel((void **)&g->graph);
	}
	free_node(g);
	free_file(&g->file);
	ft_memdel((void**)&g->capacite);
	ft_memdel((void**)&g->previous);
	ft_memdel((void**)&g->color);
	ft_memdel((void **)&g);
}

void			free_file(t_file **file)
{
	if (*file)
	{
		if ((*file)->tab)
			ft_memdel((void**)&(*file)->tab);
		ft_memdel((void**)file);
	}
}

void			free_t_tab(t_tab *t)
{
	if (t)
	{
		ft_memdel((void**)&t->tab);
		ft_memdel((void**)&t);
	}
}

void			free_besttab(t_tab ***best_tab)
{
	int i;
	int j;

	if (best_tab)
	{
		i = -1;
		while (best_tab[++i])
		{
			j = -1;
			while (best_tab[i][++j])
			{
				ft_memdel((void**)(&(best_tab[i][j]->tab)));
				ft_memdel((void**)&best_tab[i][j]);
			}
			ft_memdel((void**)(&best_tab[i]));
		}
		ft_memdel((void**)&best_tab);
	}
}
