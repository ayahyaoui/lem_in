/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:20:23 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/03 23:19:10 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
t_file			*new_file(t_graphe *g);
//t_big_tab		*new_big_tab(t_graphe *g);
t_fusion		*create_fusion(t_path *p, int max);
int				*create_tab(int taille, int val);
char			**create_double_tab(int taille, int val);

char			**create_double_tab(int taille, int val)
{
	char **map;
	int i;
	int j;

	i = 0;
	map = (char **)malloc(sizeof(char *) * taille);
	while (i < taille)
	{
		map[i] = (char *)malloc(sizeof(char) * taille);
		j = 0;
		while (j < taille)
		{
			map[i][j] = val;
			j++;
		}
		i++;
	}
	return (map);
}

int				*create_tab(int taille, int val)
{
	int		*tab;
	int		i;


	tab = (int *)malloc(sizeof(int) * taille);
	i = -1;
	while (++i < taille)
		tab[i] = val;
	return (tab);
}

t_fusion		*create_fusion(t_path *p, int max)
{
	t_fusion *fusion;
	int i;

	if(!(fusion = (t_fusion *)malloc(sizeof(t_fusion))))
		exit(3);
	fusion->nb_path = p->nb_path;
	fusion->altern = 1;
	if (!(fusion->fusion  = (t_breakdown **)malloc(sizeof(t_breakdown*) *
					(p->nb_path + 1))))
		exit(3);
	i = -1;
	while (++i < p->nb_path)
	{
		fusion->fusion[i] = (t_breakdown*)malloc(sizeof(t_breakdown));
		fusion->fusion[i]->value = p->path[i][VALUE];
		fusion->fusion[i]->cost = p->path[i][COST];
		fusion->fusion[i]->breakdown = malloc(sizeof(int) * max);
		fusion->fusion[i]->breakdown[0] = p->path[i][VALUE];
		fusion->fusion[i]->len = 1;
	}
	fusion->fusion[i] = 0x0;
	return (fusion);
}

t_big_tab		*new_big_tab(t_graphe *g)
{
	int			i;
	t_big_tab	*s;
	int			j;
	int			k;

	if (g == 0x0 || g->taille == 0)
		return (0x0);
	if (!(s = malloc(sizeof(t_big_tab))))
		exit(3);
	s->taille = g->taille;
	s->tab = create_tab(g->taille, -1);
	s->t2 = create_tab(g->taille, -1);
	s->t1 = create_tab(g->taille, -1);
	return (s);
}

t_graphe		*new_graphe(int taille)
{
	t_graphe *g;

	if(!(g = (t_graphe*)malloc(sizeof(t_graphe))))
		exit(3);
	g->taille = taille;
	g->map = create_double_tab(g->taille, 0);
	g->color = create_tab(g->taille, 0);
	return (g);
}
