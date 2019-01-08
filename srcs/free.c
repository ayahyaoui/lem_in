/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:22:17 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/08 19:52:58 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_graphe(t_graphe *g);
void			free_file(t_file **file);

void			free_graphe(t_graphe *g)
{
	int i;

	i = -1;
	if (g->map)
	{
		while ((unsigned int)++i < g->nb_rooms)
			ft_memdel((void **)&g->map[i]);
		ft_memdel((void **)&g->map);
		g->map = 0x0;
	}
	i = -1;
	if (g->graph)
	{
		ft_putstr("qwertyuiop\n");
		while ((unsigned int)++i < g->nb_rooms)
			ft_memdel((void **)&g->graph[i]);
		ft_memdel((void **)&g->graph);
		g->graph = 0x0;
	}
	ft_memdel((void**)&g->capacite);
	ft_memdel((void**)&g->previous);
	ft_memdel((void**)&g->color);
	if (g->node)
	{
		i = -1;
		while (++i < (int)g->nb_rooms)
			ft_memdel((void**)&g->node[i]);
		ft_memdel((void **)&g->node);
	}
	free_file(&g->file);
	free(g);
	g = 0x0;
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

void			free_breakdown(t_breakdown *br)
{
	if (br)
		ft_memdel((void**)&(br->breakdown));
	ft_memdel((void**)&br);
}

void			free_fusion(t_fusion *f)
{
	int i;

	i =-1;
	if (f)
	{
		if (f->fusion)
		while (f->fusion[++i])
			free_breakdown(f->fusion[i]);
		ft_memdel((void**)&f);
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

	ft_putstr("je suuuuuupppp best_tab");
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
