/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterativepath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:30:35 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/13 17:08:46 by anyahyao         ###   ########.fr       */
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
/*
int		static removepath(t_graphe *g, t_file *file)
{
	int i;
	int j;

	i = file->begin;
	while (i < file->end - 1)
	{
		j = -1;
		while (++j < (int)g->nb_rooms)
			g->map[j][file->tab[i]] = 0;
	}
}
*/
/*
int		addneighbourr(t_graphe *g, t_file *file, int node, int *tab)
{
	(void)g;
	(void)file;
	(void)node;
	(void)tab;
	return (2);
}

int				iterative_path(t_graphe *g, int *tab, t_file *file)
{
//	int			pathlen;
	int			node;
	int			find;

//	pathlen = 0;
	find = 0;
	addfile(file, g->start);
	g->color[g->start] = GREY;
	while (!isemptyfile(file))
	{
		node = removefile(file);
		if (addneighbourr(g, file, node, tab) == 2)
		{
			find = 1;
			break;
		}
		g->color[node] = BLACK;
	}
	return (find);
}


int				dijistra(t_graphe *g)
{
	int		*tab;
	t_file		*file;
	//t_tab	***res;

	file = new_file(g);
	if(!(tab = (int *)ft_memalloc(sizeof(int) * g->nb_rooms)))
		return (-1);
	if (iterative_path(g, tab, file))
	{
		displaypath(g, tab);
		
	}
	else
		ft_putstr("Il est impossible de trouver un chemin arrivant a la fin\n");
	free_file(&file);
	ft_memdel((void**)&tab);
	return(1);
}
*/
