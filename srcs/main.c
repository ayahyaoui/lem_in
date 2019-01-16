/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/17 00:14:17 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	static ENV	e;
	int			msg;

	set_env(&e);
	msg = NO_ERR;
	if (((msg = read_options(&e, argv, argc)) == NO_ERR || msg >= NO_WRNG)
			&& ((msg = read_instructions(&e, NULL)) == NO_ERR || msg >= NO_WRNG)
			&& ((msg = apply_commands(&e)) == NO_ERR || msg >= NO_WRNG))
	{
		display_anthill(&e);
		if (e.graphe->start == e.graphe->end
			|| (msg = find_best_solution(e.graphe, &e)) == NO_ERR)
		{
			free_env(&e);
			display_turns(&e);
			return (NO_ERR);
		}
	}
	return (display_error(&e, msg));
}
