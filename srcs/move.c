/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:21:36 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 22:14:52 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
** Scan all ants info and check if one of them is located in room
** Input: full path combination, maximum ant to check, room index
** return 1 if room occupied, otherwise 0
*/

static int		ant_in_room(ENV *e, int ant, int room)
{
	int		i;
	t_tab	*curpath;

	if (room == e->graphe->end)
		return (0);
	i = -1;
	while (++i < ant)
		if (e->ants[i][0] != -2 && e->all_paths[e->ants[i][0]]
				&& (curpath = e->all_paths[e->ants[i][0]][e->ants[i][1]]))
			if (curpath->tab[(int)ft_abs(e->ants[i][2])] == room)
				return (1);
	return (0);
}

/*
** For all ants, if ant in anthill, check if next room on path is free,
** and move to that room if so
** if room occuped, location index of ant is make negative to identify waiting
** status. keep in mind to always evaluate absolute value of index to check
** room occupancy
*/

void			move_next_room(ENV *e)
{
	int j;
	int ant;
	int comb;
	int	i;

	if (!e->ants)
		return ;
	ant = 0;
	while (ant < e->ins->nb_ants && e->ants[ant])
		++ant;
	j = -1;
	while (++j < ant && (i = (int)ft_abs(e->ants[j][2] + 1)))
		if ((comb = e->ants[j][0]) != -2
				&& i < (e->all_paths[comb][e->ants[j][1]])->length)
		{
			if (!ant_in_room(e, j, e->all_paths[comb][e->ants[j][1]]->tab[i]))
			{
				if (!e->ants[j][2] && e->all_paths[comb][e->ants[j][1]]->tab[0])
					--e->all_paths[comb][e->ants[j][1]]->tab[0];
				e->ants[j][2] = i;
			}
			else
				e->ants[j][2] = -i + 1;
		}
}

/*
** Scan downwards through combinations, scan upwards through paths
** check in index 0 of paths if ants are still outside the anthill and if room
** is free from ants,
** add location info to ant tab (combination, paths, index of room in path
*/

int				ant_enter_path(ENV *e, int comb)
{
	int i;
	int j;
	int ant;

	j = -1;
	while (++j < comb && (i = -1) && e->all_paths[j])
		while (e->all_paths[j][++i])
		{
			ant = 0;
			while (ant < e->ins->nb_ants && e->ants[ant])
				++ant;
			if (e->all_paths[j][i]->tab[0] && ant <= e->ins->nb_ants)
				if (!ant_in_room(e, ant, e->all_paths[j][i]->tab[1]))
				{
					if (!(e->ants[ant] = (int *)ft_memalloc(sizeof(int) * 3)))
						return (ERR_ALLOC);
					e->ants[ant][0] = j;
					e->ants[ant][1] = i;
					e->ants[ant][2] = 1;
					--e->all_paths[j][i]->tab[0];
				}
		}
	return (NO_ERR);
}
