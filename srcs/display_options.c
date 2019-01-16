/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:50:52 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 19:27:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
** Display turns, i.e. number of lines of moves display
*/

void			display_turns(ENV *e)
{
	if (!(e->options & OPT_TURNS))
		return ;
	if (e->options & OPT_COLOR)
		ft_printf("\n%s>>>>>> %d turns%s\n", COL_TURNS, e->turns, COLF_OFF);
	else
		ft_printf("\n>>>>>> %d turns%s\n", e->turns);
}

/*
** Display options
** Input: color code for options
*/

static void		display_options(ENV *e, char *col)
{
	if (!(e->options & OPT_COLOR))
		col = COLF_OFF;
	ft_printf("\n%sAvailable options: %s%s\n", col, OPTION_CHARS, COLF_OFF);
	ft_printf("\n%-*sc: %s%s\n", 10, col, COLF_OFF, OPT_C_DESCRIPTION);
	ft_printf("\n%-*sh: %s%s\n", 10, col, COLF_OFF, OPT_H_DESCRIPTION);
	ft_printf("\n%-*st: %s%s\n", 10, col, COLF_OFF, OPT_T_DESCRIPTION);
	ft_printf("\n%-*sv: %s%s\n", 10, col, COLF_OFF, OPT_V_DESCRIPTION);
	ft_printf("\n\n");
}

/*
** Display help
** Input: color code for help title, and for type titles
*/

static void		display_instructions(char *col1, char *col2)
{
	ft_printf("%s%s%s%s%s\n", COLF_BGREY, col1, HELP_TITLE, COLF_OFF, COLB_OFF);
	ft_printf("\n%s%s: %s", col2, COMMTS_NAME, COLF_OFF);
	ft_printf("%s\n", COMMTS_DESCRIPTION);
	ft_printf("- placement: %s\n- example: %s\n", COMMTS_PLACEMENT, COMMTS_EX);
	ft_printf("\n%s%s: %s", col2, COMMDS_NAME, COLF_OFF);
	ft_printf("%s\n", COMMDS_DESCRIPTION);
	ft_printf("- placement: %s\n- example: %s\n", COMMDS_PLACEMENT,
			COMMDS_EX);
	ft_printf("%s%s\n", COMMDS_NB1, COMMDS_NB2);
	ft_printf("%s:\n-%s:\n", COMMDS_AVAILABLE, COMMAND_START);
	ft_printf("%s\n-%s: %s", START_DESCRIPTION, COMMAND_END, END_DESCRIPTION);
	ft_printf("\nIf ##start or ##end command is used with number of ants or ");
	ft_printf("tube as next signficant value, it will have no effect.\n");
	ft_printf("\n%s%s: %s", col2, ANTS_NAME, COLF_OFF);
	ft_printf("%s\n", ANTS_DESCRIPTION);
	ft_printf("- placement: %s\n- example: %s\n", ANTS_PLACEMENT, ANTS_EX);
	ft_printf("\n%s%s: %s", col2, ROOM_NAME, COLF_OFF);
	ft_printf("%s\n", ROOM_DESCRIPTION);
	ft_printf("- placement: %s\n- example: %s\n", ROOM_PLACEMENT, ROOM_EX);
	ft_printf("%s%s\n", ROOM_NB1, ROOM_NB2);
	ft_printf("\n%s%s: %s", col2, TUBE_NAME, COLF_OFF);
	ft_printf("%s\n", TUBE_DESCRIPTION);
	ft_printf("%s %s %s\n", TUBE_FORWARD, TUBE_BACKWARD, TUBE_ANYWAY);
	ft_printf("- placement: %s\n- example %s\n", TUBE_PLACEMENT, TUBE_EX);
}

void			display_help(ENV *e)
{
	if (!(e->options & OPT_HELP))
		return ;
	ft_printf("----------------------------------------------------------\n\n");
	if (!(e->options & OPT_COLOR))
		display_instructions(COLB_OFF, COLF_OFF);
	else
		display_instructions(COL_HELP, COL_TYPES);
	display_options(e, COL_OPTIONS);
	ft_printf("----------------------------------------------------------\n\n");
}
