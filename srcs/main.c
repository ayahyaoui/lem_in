/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/12 22:14:23 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	display_besttab(t_tab ***tab)
{
	ft_printf("display best tab\n");
	for (int comb = 0; tab[comb]; ++comb)
	{
		ft_printf("comb # %d\n", comb);
		for (int path = 0; tab[comb][path]; ++path)
		{
			for (int i = 0; i < tab[comb][path]->length; ++i)
				ft_printf("%d ", tab[comb][path]->tab[i]);
			ft_printf("\n");

		}
		ft_printf("\n");
	}
	ft_printf("end tab\n");


}


int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static ENV	e;
	t_tab ***paths;
	int		err;
//	int		**paths; //seulement pour tester display_moves
//	char 		**names; //idem	

	set_env(&e);
	if ((err = read_options(&e, argv, argc)))
		return (display(&e, get_errmsg(err)));
	ft_printf("beginning\n");
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
//	display_adj_mtrx(&e, e.graphe->map, e.graphe->nb_rooms); 
	e.graphe->color = (int *)ft_memalloc(e.graphe->nb_rooms * sizeof(int));
//	paths  = choose_method(e.graphe);
//	paths[0][0]->tab[0] = 0;
//	paths[1][0]->tab[0] = 10;
//	paths[1][1]->tab[0] = 10;

//	display_besttab(paths);
	algoopti(e.graphe, &e);
	displayallpath(e.graphe, e.all_paths);
	paths = e.all_paths;
	ft_printf("\n\n*** final display***\n\n");
	display_allmoves(&e, paths, 0);
	//free_graphe(g);
//	display_adj_mtrx(e.graphe->map, e.graphe->nb_rooms); 
//	paths = get_pathstab(); // seulement pour tester display moves, sur une combinaison de e.nb_paths chemins
//	names = room_names(((t_input *)e.ins)->rooms, e.graphe->nb_rooms, (int **)paths, 3);
//	display_moves(&e, (int **)paths, ((t_input *)e.ins)->nb_ants);
	free_env(&e);
	return (0);
}
