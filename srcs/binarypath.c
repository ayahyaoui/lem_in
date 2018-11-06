/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarypath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 18:03:25 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/03 23:19:28 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		number_active_bit(unsigned long p, int max);
t_tab		***test_multipathbinary(t_graphe *g);
void		getallpath(t_graphe *g, t_path *path, int node
		, unsigned int p);

void		getallpath(t_graphe *g, t_path *path, int node
		, unsigned int p)
{
	int i;

	if (node == g->end)
	{
		i = -1;
		while ((unsigned int)++i < path->nb_path)
			if (path->path[i][0] == p)
				return;
		path->path[path->nb_path][VALUE] = p;
		path->path[path->nb_path][NBNODE] = number_active_bit(p, 32);
		path->nb_path = path->nb_path + 1;
		return ;
	}
	if (node == g->start && p != 0)
		return;
	if (node != 0)
		p += (1 << node);
	i = 0;
	while ((unsigned int)i < g->nb_rooms)
	{
//		ft_printf("i = %d nb rooms = %d\n", i, g->nb_rooms);
		if (g->map[node][i] && i != g->start)
		{
			if (!(p & (1 << i))){
				//ft_printf("%d=>%d  ", node, i);

				getallpath(g, path, i, p);}
		}
		++i;
	}
	g->color[node] = BLACK;
	//ft_printf("finin%d\n", node);
	//sleep(1);
}

/*
** renvois le nombre de bit actif (soit le nombre de noeud sur un chemins)
*/

int		number_active_bit(unsigned long p, int max)
{
	int i;
	int res;

	res = 0;
	i = -1;
	while (++i < max)
		if (p & 1 << i)
			res++;
	return (res);
}


t_tab	***test_multipathbinary(t_graphe *g)
{
	t_path	*p;
//	int		i;
	t_tab	***res;

	ft_printf("debut MULTI PATH\n");
	if (!g || g->nb_rooms > 32)
	{
		ft_printf("graphe trop grand pour les test\n");
		exit(1);
	}
	if (!(p = malloc(sizeof(t_path))))
			exit(3);
	p->nb_path = 0;
	ft_putstr("getallpath\n");
	getallpath(g, p, 0, 0);
	ft_printf("====il y'a %d chemins different==\n", p->nb_path);
	ft_tri_fusion_recursive_couple(p->path, p->nb_path);
//	i = 0;
	sleep(1);
	res = get_all_separpath(g, p);
	ft_printf("bien jouer\n");
	ft_memdel((void**)&p);
	return (res);
}


