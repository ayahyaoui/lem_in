/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 01:04:27 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(int argc, char **argv)
{
	static ENV	e;
	int		msg;

	set_env(&e);
	if ((msg = read_options(&e, argv, argc)))
		return (display_error(&e, msg));
	if ((msg = read_instructions(&e, NULL, 0, 0)))
	{
//		ft_printf("msg = %d\n", msg);
		if (is_failing_error(msg))
			return (display_error(&e, msg));
		display_warning(&e, msg);
	}
	if ((msg = apply_commands(&e)))
	{
		if (is_failing_error(msg))
			return (display_error(&e, msg));
		display_warning(&e,  msg);
	}
	display_anthill(&e, e.anthill);
	e.graphe->color = (int *)ft_memalloc(e.graphe->nb_rooms * sizeof(int));
//	ft_printf("\n");
	if (algoopti(e.graphe, &e) != ERR_SOLUTION)
	{
//		displayallpath(e.graphe, e.all_paths);
		int a =prediction(&e, e.graphe);
		place_ant(e.all_paths, e.ins->nb_ants, a );
		//place_ant(e.all_paths, e.ins->nb_ants, 1 );
//		displayallpath(e.graphe, e.all_paths);
		scan_allmoves(&e, DISPLAY_ON);
	/*	place_ant(e.all_paths, e.ins->nb_ants, 1 );
//		displayallpath(e.graphe, e.all_paths);
		scan_allmoves(&e, DISPLAY_OFF);
		place_ant(e.all_paths, e.ins->nb_ants, 1 );
//		displayallpath(e.graphe, e.all_paths);
		scan_allmoves(&e, DISPLAY_OFF);
//		ft_printf("prediction %d\n",a);*/
	}
	else
		return (display_error(&e, ERR_SOLUTION));
	free_env(&e);
	return (0);
}
