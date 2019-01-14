/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 22:39:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_failing_error(int err)
{
	return (err == ERR_START || err == ERR_ANT_NB || err == ERR_ANT_INPUT || err == ERR_LIB || err == ERR_ALLOC || err == ERR_START || err == ERR_SAME || err == ERR_END || err == ERR_OPTION || err == ERR_ARG || err == ERR_NOTUBE);
}


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
		if (is_failing_error(err))
		{
			free_env(&e);
			return (display(&e, get_errmsg(err)));
		}
		else if (e.options & OPT_VERBOSE)
			ft_printf("Warning: %s\n", get_errmsg(err));
	}
	if ((err = apply_commands(&e)))
	{
		if (is_failing_error(err))
		{
			free_env(&e);
			return (display(&e, get_errmsg(err)));
		}
		else if (e.options & OPT_VERBOSE)
			ft_printf("Warning: %s\n", get_errmsg(err));

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
