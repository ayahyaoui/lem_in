/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 18:15:41 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static ENV	e;
	int		err;

	set_env(&e);
	if ((err = read_options(&e, argv, argc)))
		return (display(&e, get_errmsg(err)));
	if ((err = read_instructions(&e, NULL, 0, 0)))
	{
		free_env(&e);
		return (display(&e, get_errmsg(err)));

	}
	if ((err = apply_commands(&e)))
	{
		free_env(&e);
		return (display(&e, get_errmsg(err)));
	}
	display_anthill(e.anthill);
	e.graphe->color = (int *)ft_memalloc(e.graphe->nb_rooms * sizeof(int));
	ft_printf("\n");
	if (algoopti(e.graphe, &e) != ERR_SOLUTION)
		scan_allmoves(&e, DISPLAY_ON);
	else
		return (display(&e, get_errmsg(ERR_SOLUTION)));
	free_env(&e);
	return (0);
}
