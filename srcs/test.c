/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:39:32 by anyahyao          #+#    #+#             */
/*   Updated: 2018/12/09 17:47:19 by anyahyao         ###   ########.fr       */
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
/*
void	test_mapdemoniaque(t_graphe *g)
{
	if (g->nb_rooms < 12)
		return;
	addlink(g, 0, 1);
	addlink(g, 0, 3);
	addlink(g, 1, 2);
	addlink(g, 1, 7);
	addlink(g, 2, 6);
	addlink(g, 2,10);
	addlink(g, 3, 4);
	addlink(g, 4, 5);
	addlink(g, 5, 6);
	addlink(g, 6, 2);
	addlink(g, 7, 8);
	addlink(g, 8, 9);
	addlink(g, 9,10);
	g->start = 0;
	g->end = 10;
}
*/
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

int			choose_method(t_graphe *g, t_input *info)
{
	//t_tab ***best_tab = 0X0;
	//ft_printf("choisemethodse\n");
/*	if (g->nb_rooms < 16)
		best_tab = test_multipathbinary(g);
	else
		dijistra(g);

	add_ant(g, best_tab, 10);
	displayallpath(g, best_tab);
	free_besttab(best_tab);
*/
	convert(g, info);
	return (1);
}
/*
int main(int argc, const char *argv[])
{
	t_graphe *g;
	unsigned int i;
//	int j;

	(void)argc;
	(void)argv;
	g = new_graphe(13);

	g->start = 0;
	g->end = 7;
	test_mapdemoniaque(g);
	for (i = 0; i < g->nb_rooms ;i++) {
		g->map[i][i] = 0;
	}
	choosemethod(g);
	free_graphe(g);
	//exit(1);
	return (0);
}*/
