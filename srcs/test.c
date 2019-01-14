/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:39:32 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/13 18:01:43 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	afficheAllParent(t_graphe *g);

/*
 *	short_path renvois la taille du chemin le plus cours en begin et endif
 *	return -1 en cas impossibilite
 *
 */


void	tab_swap(int **a, int **b)
{
	int *c;
	c = *a;
	*a = *b;
	*b = c;
}

void			ft_mem_set_int(int *tab, int val, int taille)
{
	int i;

	if (!tab)
		exit(1);
	i = -1;
	while (++i < taille)
		tab[i] = val;
}

int		addlink(t_graphe *g, unsigned int a, unsigned int b)
{
	if (g->nb_rooms > a && g->nb_rooms > b && a != b)
	{
		g->map[a][b] = 1;
		g->map[b][a] = 1;
		return (1);
	}
	return(0);
}

void	afficheAllParent(t_graphe *g)
{
	unsigned int i = 0;
	t_node *node;
	printf("============\n");
	while (i < g->nb_rooms)
	{
		if (g->map[i][g->end] == 1 && g->node[i]->parent >= 0)
		{
			node = g->node[i];
			int j = -1;
			while (node->value != g->start)
			{ ++j;
				printf("(%d)<-",node->value);
				node = g->node[node->parent];
				if (node->value == 1333 && j > 15)
					exit(1);
			}
			printf("(%d)\n", g->start);
		}
		i++;
	}
	ft_bzero(g->color, g->nb_rooms * 4);
	for (i = 0; i < g->nb_rooms; i++) {
		if (g->node[i]->parent > 0)
			g->color[g->node[i]->parent]++;
		if (g->node[i]->parent == 398)
			printf("398---->%d\n", i);
	}
	for (i = 0; i < g->nb_rooms; i++) 
		if (g->color[i] > 1){
			ft_printf("probleme en %d<-%d", i, g->node[i]->parent);
			exit(1);
		}
	/*for (i = 0; i < g->nb_rooms; i++) {
		if (g->color[i] > 1)
			ft_printf("probleme en %d<-%d", i, g->node[i]->parent);
	}*/
	ft_bzero(g->color, g->nb_rooms);
			//printf("%d(%d) //// ", g->node[i]->parent, i);
}


