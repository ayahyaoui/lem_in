/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:22:17 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/01 19:48:54 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			free_graphe(t_graphe *g);
void			free_file(t_file **file);

void			free_graphe(t_graphe *g)
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
	ft_memdel((void**)&g->color);
	free(g);
	g = 0x0;
}


void			free_file(t_file **file)
{
	if (*file)
	{
		if ((*file)->tab)
			ft_memdel((void**)&(*file)->tab);
		ft_memdel((void**)file);
	}
}
