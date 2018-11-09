/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:22:17 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/08 15:40:56 by emuckens         ###   ########.fr       */
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
	}
	ft_memdel((void**)&g->color);
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

	if (best_tab)
	{
		i = -1;
		while (best_tab[++i])
		{
			j = -1;
			while (best_tab[i][++j])
				ft_memdel((void**)(&best_tab[i][j]->tab));
		}
	}
}