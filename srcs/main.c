/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/09 16:13:13 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
/*
static int	**get_pathstab()
{
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
	return (paths);
}
*/


void	display_besttab(t_tab ***tab)
{
	ft_printf("display best tab\n");
	for (int comb = 0; tab[comb]; ++comb)
	{
		for (int path = 0; tab[comb][path]; ++path)
			for (int i = 0; i < tab[comb][path]->length; ++i)
				ft_printf("%d ", tab[comb][path]->tab[i]);
//			ft_print_inttab(tab[comb][path]->tab, tab[comb][path]->length, ' ');
		ft_printf("\n");
	}


}



t_tab ***get_pathstab()
{
	t_tab ***all;
	int comb;
	int path;

	int trois1[6] = {4, 0, 10, 13, 14, 15};
	int trois2[6] = {5, 1, 3, 5, 6, 8};
	int trois3[5] = {6, 2, 4, 7, 9};
	int	deux1[5] = {6, 1, 3, 7, 9};
	int	deux2[5] = {4, 0, 10, 13, 6};
	int un[5] = {5, 0, 10, 13, 6};


	comb = -1;
	all = (t_tab ***)ft_memalloc(sizeof(t_tab **) * 4);
	while (++comb < 3)
	{
		all[comb] = (t_tab **)ft_memalloc(sizeof(t_tab *) * (4 - comb));
		path = -1;
		while (++path < 4 - comb)
		{
			all[comb][path] = (t_tab *)ft_memalloc(sizeof(t_tab));
			all[comb][path]->tab = (int *)ft_memalloc(sizeof(int) * 6);
		}

	}
	all[0][0]->length = 6;
	all[0][1]->length = 6;
	all[0][2]->length = 5;
	all[1][0]->length = 5;
	all[1][1]->length = 5;
	all[2][0]->length = 5;

	for (int j = 0; j < 3; ++j)
		all[0][j]->tab = (int *)ft_memalloc(sizeof(int) * all[0][j]->length);
	for (int j = 0; j < 2; ++j)
		all[1][j]->tab = (int *)ft_memalloc(sizeof(int) * all[1][j]->length);
	all[2][0]->tab = (int *)ft_memalloc(sizeof(int) * all[2][0]->length);
	ft_memmove(&all[0][0]->tab, trois1, sizeof(trois1));
	ft_memmove(&all[0][1]->tab, trois2, sizeof(trois2));
	ft_memmove(&all[0][2]->tab, trois3, sizeof(trois3));
	ft_memmove(&all[1][0]->tab, deux1, sizeof(deux1));
	ft_memmove(&all[1][1]->tab, deux2, sizeof(deux2));
	ft_memmove(&all[2][0]->tab, un, sizeof(un));
	
	display_besttab(all);
	return (all);

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
	paths  = choose_method(e.graphe);
	display_besttab(paths);
//	paths = get_pathstab();
	display_allmoves(&e, paths, 0);

//	display_adj_mtrx(e.graphe->map, e.graphe->nb_rooms); 
//	paths = get_pathstab(); // seulement pour tester display moves, sur une combinaison de e.nb_paths chemins
//	names = room_names(((t_input *)e.ins)->rooms, e.graphe->nb_rooms, (int **)paths, 3);
//	display_moves(&e, (int **)paths, ((t_input *)e.ins)->nb_ants);
	free_env(&e);
	return (0);
}
