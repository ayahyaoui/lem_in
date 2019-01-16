/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 06:08:36 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 06:15:39 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** At end room index, display antname in color if option actived
** Input: all combination of paths, number of ant
** return 1 if calling function should call regular room index display instead
*/

static int		display_ant_at_end(ENV *e, t_tab ***paths, int ant, int display)
{
	int path;
	int comb;
	int room;

	if (!e->ants[ant - 1] || e->ants[ant - 1][2] <= 0)
		return (0);
	comb = e->ants[ant - 1][0];
	path = e->ants[ant - 1][1];
	room = e->ants[ant - 1][2];
	if (comb != -2 && paths[comb][path]->tab[room] == e->graphe->end)
	{
		if (display && e->options & OPT_COLOR)
			ft_printf("{CYAN}L%d-%s{EOC} ", ant,
					e->ins->room[paths[comb][path]->tab[room]].name);
		else if (display)
		{
			ft_printf("L%d-%s ", ant,
					e->ins->room[paths[comb][path]->tab[room]].name);
		}
		e->ants[ant - 1][0] = -2;
		return (1);
	}
	return (comb != -2 ? 0 : 1);
}

/*
** Scan ants, display end format if end room index detected,
** else display regular ant location
** return number of ants arrived, to stop program when all have arrived
*/

int				display_travelling(ENV *e, t_tab ***paths, int display)
{
	int ant;
	int arrived;
	int	i;

	ant = -1;
	arrived = 0;
	++e->turns;
	while (++ant < e->ins->nb_ants && e->ants && e->ants[ant] >= 0)
	{
		if ((display_ant_at_end(e, paths, ant + 1, display)))
			++arrived;
		else if (e->ants[ant])
		{
			i = paths[e->ants[ant][0]][e->ants[ant][1]]->tab[e->ants[ant][2]];
			if (e->ants[ant][2] > 0 && display)
				ft_printf("L%d-%s ", ant + 1, e->ins->room[i].name);
		}
	}
	ft_printf("%s", display ? "\n" : "");
	return (arrived);
}
