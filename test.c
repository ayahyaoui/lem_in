/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:39:32 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/03 00:01:55 by anyahyao         ###   ########.fr       */
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

int			choosemethod(t_graphe *g)
{
	//ft_printf("choisemethodse\n");
	if (g->taille < 16)
		test_multipathbinary(g);
	else
		dijistra(g);
	return (1);
}


int main(int argc, const char *argv[])
{
	t_graphe *g;
	int i;
	int j;

	g = new_graphe(8);

	g->begin = 0;
	g->end = 7;

	for (i = 0; i < g->taille ;i++) {
//		g->map[g->end][i] = 0;
		g->map[i][i] = 0;
//		g->map[i][g->end] = 0;
	}

//	g->map[g->end][2] = 1;
//	g->map[2][g->end] = 1;

	choosemethod(g);
	free_graphe(g);
	//exit(1);
	return (0);
}
