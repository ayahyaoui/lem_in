/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_repart_ant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:08:18 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/16 23:01:49 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		place_ant(t_tab ***besttab, int fourmis, int path)
{
	int i;
	int j;
	int	nb_chemin;
	int pass;

	nb_chemin = 0;
	while (besttab[path][nb_chemin])
		nb_chemin++;
	i = nb_chemin;
	while (fourmis > 0)
	{
		pass = 0;
		j = -1;
		while (++j < nb_chemin)
			if (i >= besttab[path][j]->length)
			{
				pass++;
				besttab[path][j]->tab[0]++;
				if (fourmis - pass == 0)
					return (i);
			}
		fourmis -= pass;
		i++;
	}
	return (i);
}

static void		clean_ant(t_tab ***besttab)
{
	int i;
	int j;

	i = -1;
	while (besttab[++i])
	{
		j = -1;
		while (besttab[i][++j])
			besttab[i][j]->tab[0] = 0;
	}
}

static void		change_place_ant(t_graphe *g, int *tab)
{
	int i;

	i = -1;
	while (++i <= g->nb_paths && tab[i] == 0)
		;
	if (i > 0)
	{
		tab[i - 1] = tab[i];
		tab[i] = 0;
	}
}

int				*prediction(ENV *e, t_graphe *g)
{
	int *best_comb;
	int *last_comb;
	int cost_best;

	ft_bzero(g->color, sizeof(int) * g->nb_rooms);
	ft_bzero(g->previous, sizeof(int) * g->nb_rooms);
	best_comb = g->color;
	last_comb = g->previous;
	last_comb[g->nb_paths] = e->ins->nb_ants;
	best_comb[g->nb_paths] = e->ins->nb_ants;
	cost_best = -1;
	while (42)
	{
		try_to_place_ant(e->all_paths, last_comb);
		scan_allmoves(e, DISPLAY_OFF);
		if (e->turns > 0 && (e->turns < cost_best || cost_best == -1))
		{
			cost_best = e->turns;
			ft_memmove(best_comb, last_comb, (g->nb_paths + 1) * sizeof(int));
		}
		if (last_comb[0] == e->ins->nb_ants)
			break ;
		change_place_ant(g, last_comb);
	}
	return (best_comb);
}

int				try_to_place_ant(t_tab ***besttab, int *tab_fourmis)
{
	int i;

	clean_ant(besttab);
	i = -1;
	while (besttab[++i])
		if (tab_fourmis[i] > 0)
			place_ant(besttab, tab_fourmis[i], i);
	return (1);
}
