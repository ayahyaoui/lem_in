/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:39:32 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/01 20:24:05 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


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
/*
void	free_path(t_path *p)
{
	if (p)
	{
		if(p->path)
		{
			free(p->path);
			p->path = 0x0;
		}
		free(p);
		p = 0x0;
	}
}*/

void	test_map(t_graphe *g)
{
	g->map[0][1] = 1;
	g->map[1][0] = 1;
	g->map[1][3] = 1;
	g->map[3][1] = 1;
	g->map[3][5] = 1;
	g->map[5][3] = 1;
	g->map[0][4] = 1;
	g->map[4][0] = 1;
	g->map[4][5] = 1;
	g->map[5][4] = 1;
	g->map[2][5] = 1;
	g->map[5][2] = 1;
	g->map[0][2] = 1;
	g->map[2][0] = 1;
	g->map[1][2] = 1;
	g->map[2][1] = 1;
}

int main(int argc, const char *argv[])
{
	t_graphe *g;
	int i;
	int j;

	g = new_graphe(50000);
	g->map[0][0] = 0;
	g->map[1][1] = 0;
	g->map[2][2] = 0;
	g->map[3][3] = 0;
	g->map[0][3] = 0;
	g->begin = 0;
	g->end = 7;
	for (i = 0; i < g->taille ;i++) {
		g->map[g->end][i] = 0;
		g->map[i][g->end] = 0;
	}
	
	g->map[g->end][g->begin + 1] = 1;
	g->map[g->begin + 1][g->end] = 1;
	//test_map(g);
/*	t_big_tab *bt = new_big_tab(g);
	if (argc == 1)
	{
		printf("%d", short_path(g, bt, 1023, 0));
	//	test_init_all_path(g, g->taille-1);
	}
	else*/ /*if (argc == 3)
	{
	//	i = ft_atoi(argv[1]);
	//	j = ft_atoi(argv[2]);
		//printf("%d", short_path(g, bt, i, j));
		test_init_all_path(g, 3);
	}*/
	dijistra(g);
	free_graphe(g);
	return 0;
}
