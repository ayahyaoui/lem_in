/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:46:40 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/13 17:06:11 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


/*

int		check_path_len(t_graphe *g, t_big_tab *bt, int k, int node)
{
	int i;

	i = 0;
	while ((unsigned int)i < g->nb_rooms)
	{
		if (g->map[node][i] != 0 && (bt->tab[i] == -1 || bt->tab[i] >
					g->map[node][i] + bt->tab[node]))
		{
			bt->tab[i] = g->map[node][i] + bt->tab[node];
			bt->t2[k] = i;
			k++;
		}
		i++;
	}
	return (k);
}


void			reboot_big_tab(t_big_tab *bt, int begin)
{
	int i;

	i = 0;
	while ((unsigned int)i < bt->taille)
	{
		bt->tab[i] = -1;
		bt->t1[i] = -1;
		bt->t2[i] = -1;
		i++;
	}
	bt->tab[begin] = 0;
	bt->t1[0] = begin;
}
*/
/*
int				short_path(t_graphe *g, t_big_tab *bt, unsigned int begin, unsigned int end)
{
	int i;
	int j;
	int k;

	if (begin > g->nb_rooms || end > g->nb_rooms)
		return (-1);
	if (begin == end)
		return (0);
	reboot_big_tab(bt, begin);
	i = 0;
	while ((unsigned int)i < g->nb_rooms)
	{
		j = 0;
		k = 0;
		// nettoie le bt->t2 avec des -1 (memset pour les int)
		ft_mem_set_int(bt->t2, -1, bt->taille);
		while (bt->t1[j] != -1)
		{
			k = check_path_len(g, bt, k, bt->t1[j]);
			j++;
		}
		tab_swap(&bt->t1, &bt->t2);
		i++;
	}
	ft_print_inttab(bt->tab,bt->taille,' ');
	printf("\n");
	return (bt->tab[end]);
}*/
