/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:29:03 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/01 20:29:06 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			displaypath(t_graphe *g, int *tab);
void		affiche_path(t_path *p);


void		affiche_path(t_path *p)
{
	int i;

	for (i = 0; i < p->nb_path; i++)
	{
		ft_printnbit((int)p->path[i][VALUE], 6);
		printf("==>%u = %u\n", p->path[i][VALUE], p->path[i][COST]);
	}
}
/*
 *	displaypath pas secur
 */
int			displaypath(t_graphe *g, int *tab)
{
	int node;

	node = g->end;
	while (node != g->begin)
	{
		ft_printf("%d<-",node);
		node = tab[node];
	}
	ft_printf("%d\n", node);
	return (1);
}
