/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:34 by anyahyao          #+#    #+#             */
/*   Updated: 2018/09/30 21:04:03 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


/*
 *	short_path renvois la taille du chemin le plus cours en begin et endif
 *	return -1 en cas impossibilite
 *
 */


int		**create_double_tab(int taille, int val)
{
	int **map;
	int i;
	int j;

	i = 0;
	map = (int **)malloc(sizeof(int *) * taille);
	while (i < taille)
	{
		map[i] = (int *)malloc(sizeof(int) * taille);
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

void	tab_swap(int **a, int **b)
{
	int *c;
	c = *a;
	*a = *b;
	*b = c;
}

int		*create_tab(int taille, int val)
{
	int		*tab;
	int		i;


	tab = (int *)malloc(sizeof(int) * taille);
	i = -1;
	while (++i < taille)
		tab[i] = val;
	return (tab);
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

void	free_graphe(t_graphe *g)
{
	int i;

	i = -1;
	while (++i < g->taille)
	{
		free(g->map[i]);
		g->map[i] = 0x0;
	}
	free(g->map);
	g->map = 0x0;
	free(g);
	g = 0x0;
}

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

}

int main(int argc, const char *argv[])
{
	t_graphe *g;
	int i;
	int j;

	g = (t_graphe*)malloc(sizeof(t_graphe) * 2);
	g->taille = 6;
	g->map = create_double_tab(g->taille, 0);
	test_map(g);
	t_big_tab *bt = new_big_tab(g);
	if (argc == 1)
		printf("%d", short_path(g, bt, 0, 5));
	else if (argc == 3)
	{
		printf("%d", short_path(g, bt, ft_atoi(argv[1]), ft_atoi(argv[2])));
	}
	free_graphe(g);
	return 0;
}
