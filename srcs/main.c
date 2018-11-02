/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 23:20:19 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static ENV	e;
	int			err;

	set_env(&e);
	if ((err = read_instructions(&e, NULL, 0, 0)))
		return (display(&e, get_errmsg(err)));
	e.graphe->nb_rooms = ft_lstsize(e.ins->rooms);
	display_adj_mtrx(e.graphe->map, e.graphe->nb_rooms); 
	
	int **paths;
	int i = -1;
	paths = (int **)ft_memalloc(sizeof(int *) * 3); 
	while (++i < 5)
		paths[i] = (int *)ft_memalloc(sizeof(int) * 5);
	paths[0][0] = 5;
	paths[0][1] = 5;
	paths[0][2] = -1;
	paths[0][3] = -1;
	paths[0][4] = -1;
	paths[1][0] = 4;
	paths[1][1] = 3;
	paths[1][2] = 4;
	paths[1][3] = -1;
	paths[1][4] = -1;
	paths[2][0] = 2;
	paths[2][1] = 2;
	paths[2][2] = 0;
	paths[2][3] = 1;
	paths[2][4] = -1;

	char **names;
	e.nb_paths = 3;
	names = room_names(((t_input *)e.ins)->rooms, e.graphe->nb_rooms, (int **)paths, 3);
	display_moves(&e, (int **)paths, names, ((t_input *)e.ins)->nb_ants);
				


	return (0);
}
