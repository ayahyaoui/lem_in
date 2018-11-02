/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getgraphe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 17:43:57 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/02 17:52:31 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			degre_graphe(t_graphe *g)
{
	int i;
	int res;
	int j;

	if (g == 0X0)
		return (-1);
	i = -1;
	res = 0;
	while (++i < g->taille)
	{
		j = -1;
		while (++j < g->taille)
			if(g->map[i][j])
				res++;
	}
	return (res / 2);
}

/*
**	renvois le nombre de voisin d'un noeud
*/

int			degre(t_graphe *g, int node)
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (++i < g->taille)
		if (g->map[node][i])
			res++;
	return (res);
}


