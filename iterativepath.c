/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterativepath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:30:35 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/01 20:28:11 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 * iterative_path prend en param 
 *				-g le graphe
 *				-tab un tableau de taille g->tab qui va contenir le chemin
 *				-begin pos du debut
 *				-end	pos de fin
 * remarque
 *	par du principe que tous les node sont blanc
 *	all node are white
 *	si on veut appele plusieur fois iterative_path vaut mieux faire sortir 
 *	la file pour l'allouer 1 seule fois
 *	le debut et different de la fin
 */

int		addneighbour(t_graphe *g, t_file *file, int node, int *tab)
{
	int i;

	i = -1;
	while (++i < g->taille)
	{
		if (g->color[i] == WHITE && g->map[i][node] == 1)
		{
			g->color[i] = GREY;
			addfile(file, i);
			tab[i] = node;
			if (i == g->end)
				return (2);
		}
	}
	return (1);
}

int				iterative_path(t_graphe *g, int *tab, t_file *file)
{
	int			pathlen;
	int			node;
	int			find;

	pathlen = 0;
	find = 0;
	addfile(file, g->begin);
	g->color[g->begin] = GREY;
	while (!isemptyfile(file))
	{
		node = removefile(file);
		if (addneighbour(g, file, node, tab) == 2)
		{
			find = 1;
			break;
		}
		g->color[node] = BLACK;
		ft_putstr("first\n");
	}
	return (find);
}


int				dijistra(t_graphe *g)
{
	int		*tab;
	t_file		*file;

	file = new_file(g);
	if(!(tab = (int *)ft_memalloc(sizeof(int) * g->taille)))
		exit (3);
	if (iterative_path(g, tab, file))
		displaypath(g, tab);
	else
		ft_putstr("Il est impossible de trouver un cheimin arrivant a la fin\n");
	free_file(&file);
	free(tab);
	return(1);
}
