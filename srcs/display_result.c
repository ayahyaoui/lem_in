/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 06:08:36 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 23:03:11 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
** At end room index, display antname in color if option actived
** Input: all combination of paths, number of ant
** return 1 if calling function should call regular room index display instead
*/

static int		display_ant_at_end(ENV *e, int ant, int display)
{
	int path;
	int comb;
	int room;

	if (!e->ants[ant - 1] || e->ants[ant - 1][2] <= 0)
		return (0);
	comb = e->ants[ant - 1][0];
	path = e->ants[ant - 1][1];
	room = e->ants[ant - 1][2];
	if (comb != -2 && e->all_paths[comb][path]->tab[room] == e->graphe->end)
	{
		if (display && e->options & OPT_COLOR)
			ft_printf("{CYAN}L%d-%s{EOC} ", ant,
					e->ins->room[e->all_paths[comb][path]->tab[room]].name);
		else if (display)
		{
			ft_printf("L%d-%s ", ant,
					e->ins->room[e->all_paths[comb][path]->tab[room]].name);
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

int				display_travelling(ENV *e, int display)
{
	int arrived;
	int	j;
	int i;

	i = -1;
	arrived = 0;
	++e->turns;
	while (++i < e->ins->nb_ants && e->ants && e->ants[i] >= 0)
	{
		if ((display_ant_at_end(e, i + 1, display)))
			++arrived;
		else if (e->ants[i])
		{
			j = e->all_paths[e->ants[i][0]][e->ants[i][1]]->tab[e->ants[i][2]];
			if (e->ants[i][2] > 0 && display)
				ft_printf("L%d-%s ", i + 1, e->ins->room[j].name);
		}
	}
	ft_printf("%s", display ? "\n" : "");
	return (arrived);
}

/*
** Display whole anthill on termnal
*/

void			display_anthill(ENV *e)
{
	t_list *tmp;

	tmp = e->anthill;
	while (tmp && tmp->content && e->nb_line--)
	{
		ft_printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}
