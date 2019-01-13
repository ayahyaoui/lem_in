/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:04:49 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/13 21:54:57 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

/*
 ** Display whole anthill on termnal
 */

void		display_anthill(t_list *anthill)
{
	t_list *tmp;

	tmp = anthill;
	while (tmp)
	{
		ft_printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}


/*
** At end room index, display antname in color if option actived
** Input: all combination of paths, number of ant
** return 1 if calling function should call regular room index display instead
*/

static int		display_ant_at_endlocation(ENV *e, t_tab ***paths, int ant)
{

	int path;
	int comb;
	int room;

//	ft_printf("ant = %d\n", ant);
	if (!e->ants[ant - 1] || !e->ants[ant - 1][2])
		return (1);
	comb = e->ants[ant - 1][0];
	path = e->ants[ant - 1][1];
	room = e->ants[ant - 1][2];
//	ft_printf("end location ant = %d comb = %d path = %d room = %d\n", ant, comb, path, room);
//	if (comb >= 0)
//		ft_printf("display at end location, comb = %d path = %d room = %d room name = %d\n", comb, path, room, paths[comb][path]->tab[room]);
	if (comb != -2 && paths[comb][path]->tab[room] == e->graphe->end)
	{
		if (e->options & OPT_COLOR)
			ft_printf("{CYAN}L%d-%s{EOC} ", ant,
				e->ins->room[paths[comb][path]->tab[room]].name);
		else
			ft_printf("L%d-%s ", ant,
				e->ins->room[paths[comb][path]->tab[room]].name);

		e->ants[ant - 1][0] = -2;
		return (1);
	}
	return (comb != -2 ? 0 : 1);
}





/*
 ** Scan ants, display end format if end room index detected, else display regular ant location
** return number of ants arrived, to stop program when all have arrived
 */

int		display_travelling(ENV *e, t_tab ***paths)
{
	int ant;
	int arrived;
	int	roomindex;

	ant = 0;
	arrived = 0;
//		ft_printf("ant = %d nbants = %d ants[ant] = %d\n", ant, e->ins->nb_ants, e->ants[ant]);
	++e->turns;
	while (ant < e->ins->nb_ants /*&& e->ants[ant]*/)
	{	
//		if (e->ants[ant + 1]/* && e->ants[ant][0] != -2*/)
//		{
//		ft_printf("ant = %d nbants = %d ants[ant] = %d\n", ant, e->ins->nb_ants, e->ants[ant]);
		if (/*e->ants[ant + 1] &&*/ display_ant_at_endlocation(e, paths, ant + 1))
			++arrived;
	
		else// if (e->ants[ant])
		{
			roomindex = paths[e->ants[ant][0]][e->ants[ant][1]]->tab[e->ants[ant][2]];
			ft_printf("L%d-%s ", ant + 1, e->ins->room[roomindex].name);
		}
//		}
		++ant;
	}
	ft_printf("\n");
	return (arrived);
}

/*
 ** loops through moves and display result
 ** one move comprises: moving all ants in anthill to the next room (when possible), introducing new ants in
 ** anthill (if enough ants and free rooms)
 */

int		display_allmoves(ENV *e, t_tab ***paths, int arrived)
{
	int	nb_comb;
	int	high_comb;

	nb_comb = 0;
	//paths[0][0]->tab[0] = 5;
	while (paths[nb_comb])
		++nb_comb;
	high_comb = nb_comb;
	if (!(e->ants = (int **)ft_memalloc(sizeof(int *) * (e->ins->nb_ants + 1))))
		return (ERR_ALLOC);
	ft_printf("arrived = %d nb ants = %d\n", arrived, e->ins->nb_ants);
//	e->ants[e->ins->nb_ants] = NULL;
	while (arrived < e->ins->nb_ants)
	{
		move_next_room(e, paths);
		ant_enter_path(e, paths, high_comb - 1);
		arrived = display_travelling(e, paths);
//		ft_printf("ARRIVED = %d nb ants = %d\n", arrived, e->ins->nb_ants);
		nb_comb = high_comb;
	}
	if (e->options & OPT_TURNS)
		ft_printf("\n>>>>>> %d turns\n", e->turns);
	return (NO_ERR);
}

