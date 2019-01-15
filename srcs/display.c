/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:04:49 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/15 18:30:09 by emuckens         ###   ########.fr       */
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
	while (tmp && tmp->content)
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

	if (!e->ants[ant - 1])
		return (0);
	if (e->ants[ant - 1][2] <= 0)
		return (0);
	comb = e->ants[ant - 1][0];
	path = e->ants[ant - 1][1];
	room = e->ants[ant - 1][2];
	if (comb != -2 && paths[comb][path]->tab[room] == e->graphe->end)
	{
		if (e->options & OPT_COLOR)
			ft_printf("{CYAN}L%d-%s{EOC} ", ant,
				e->ins->room[paths[comb][path]->tab[room]].name);
		else
		{
			ft_printf("L%d-%s ", ant,
				e->ins->room[paths[comb][path]->tab[room]].name);
		}

		e->ants[ant - 1][0] = -2;
		return (1);
	}
	return (comb != -2 ? 0 : 1);
}

void		display_options(char *col)
{
	ft_printf("\n%sAvailable options: %s%s\n", col, OPTION_CHARS, COLF_OFF);
	ft_printf("\n%-*sc: %s%s\n", 10, col, COLF_OFF, OPT_C_DESCRIPTION); 
	ft_printf("\n%-*sh: %s%s\n", 10, col, COLF_OFF,  OPT_H_DESCRIPTION); 
	ft_printf("\n%-*st: %s%s\n", 10, col, COLF_OFF, OPT_T_DESCRIPTION); 
	ft_printf("\n%-*sv: %s%s\n", 10, col, COLF_OFF, OPT_V_DESCRIPTION); 
	ft_printf("\n\n");
}

void		display_help(char *col1, char *col2)
{
	ft_printf("-----------------------------------------------------------------------------\n");
	ft_printf("\n\n%s%s%s%s%s\n", COLF_BGREY, col1, HELP_TITLE, COLF_OFF, COLB_OFF);
	ft_printf("\n%s%s: %s", col2, COMMENTS_NAME, COLF_OFF);
	ft_printf("%s\n", COMMENTS_DESCRIPTION);
	ft_printf("- placement: %s\n", COMMENTS_PLACEMENT);
	ft_printf("- example: %s\n", COMMENTS_EXAMPLE);
	ft_printf("\n%s%s: %s", col2, COMMANDS_NAME, COLF_OFF);
	ft_printf("%s\n", COMMANDS_DESCRIPTION);
	ft_printf("- placement: %s\n", COMMANDS_PLACEMENT);
	ft_printf("- example: %s\n", COMMANDS_EXAMPLE);
	ft_printf("%s%s\n", COMMANDS_NB1, COMMANDS_NB2);
	ft_printf("%s:\n-%s: %s\n-%s: %s\n", COMMANDS_AVAILABLE, COMMAND_START, START_DESCRIPTION,  COMMAND_END, END_DESCRIPTION);
	ft_printf("If ##start or ##end command is used with number of ants or tube as next signficant value, ");
	ft_printf("it will have no effect.\n");
	ft_printf("\n%s%s: %s", col2, ANTS_NAME, COLF_OFF);
	ft_printf("%s\n", ANTS_DESCRIPTION);
	ft_printf("- placement: %s\n", ANTS_PLACEMENT);
	ft_printf("- example: %s\n", ANTS_EXAMPLE);
	ft_printf("\n%s%s: %s", col2, ROOM_NAME, COLF_OFF);
	ft_printf("%s\n", ROOM_DESCRIPTION);
	ft_printf("- placement: %s\n", ROOM_PLACEMENT);
	ft_printf("- example: %s\n", ROOM_EXAMPLE);
	ft_printf("%s%s\n", ROOM_NB1, ROOM_NB2);
	ft_printf("\n%s%s: %s", col2, TUBE_NAME, COLF_OFF);
	ft_printf("%s\n", TUBE_DESCRIPTION);
	ft_printf("%s %s %s\n", TUBE_FORWARD, TUBE_BACKWARD, TUBE_ANYWAY);
	ft_printf("- placement: %s\n", TUBE_PLACEMENT);
	ft_printf("- example: %s\n", TUBE_EXAMPLE);
	display_options(COL_OPTIONS);
	ft_printf("-----------------------------------------------------------------------------\n");
}


/*
 ** Scan ants, display end format if end room index detected, else display regular ant location
** return number of ants arrived, to stop program when all have arrived
 */

int		display_travelling(ENV *e, t_tab ***paths, int display)
{
	int ant;
	int arrived;
	int	roomindex;
	int	ret; //

	ant = 0;
	arrived = 0;
	++e->turns;
	while (ant < e->ins->nb_ants && e->ants && e->ants[ant])
	{	
		if ((ret = display_ant_at_endlocation(e, paths, ant + 1)))
			++arrived;
		else  if (display && e->ants[ant])
		{
			roomindex = paths[e->ants[ant][0]][e->ants[ant][1]]->tab[e->ants[ant][2]];
			if (e->ants[ant][2] > 0)
				ft_printf("L%d-%s ", ant + 1, e->ins->room[roomindex].name);
		}
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
// DISPLAY_ON ou DISPLAY_OFF

int		scan_allmoves(ENV *e, int display)
{
	int	nb_comb;
	int	high_comb;
//	int	i;
	int arrived;

	nb_comb = 0;
	arrived = 0;
	e->turns = 0;

	if (!e->all_paths)
		return (display_error(e, ERR_SOLUTION));
		ft_printf("comb = %d\n", nb_comb);
	while (e->all_paths[nb_comb])
	{
		++nb_comb;
	}
	high_comb = nb_comb;
	if (!e->ants)
	{
		if (!(e->ants = (int **)ft_memalloc(sizeof(int *) * (e->ins->nb_ants + 1))))
			return (ERR_ALLOC);
	}
		else
			ft_bzero(&e->ants, sizeof(e->ants));
	while (arrived < e->ins->nb_ants)
	{
		move_next_room(e, e->all_paths);
		ant_enter_path(e, e->all_paths, high_comb);
		arrived = display_travelling(e, e->all_paths, display);
	}
	if (display && e->options & OPT_TURNS)
		ft_printf("\n>>>>>> %d turns\n", e->turns);
	return (NO_ERR);
}

