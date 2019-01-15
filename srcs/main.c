/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/15 18:31:36 by emuckens         ###   ########.fr       */
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
	display_anthill(e.anthill);
	e.graphe->color = (int *)ft_memalloc(e.graphe->nb_rooms * sizeof(int));
	ft_printf("\n");
	if (algoopti(e.graphe, &e) != ERR_SOLUTION)
	{
		scan_allmoves(&e, DISPLAY_ON);
	}
	else
		return (display_error(&e, ERR_SOLUTION));
	free_env(&e);
	return (0);
}
