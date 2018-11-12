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
	paths  = choose_method(e.graphe);
	paths[0][0]->tab[0] = 0;
	paths[1][0]->tab[0] = 10;
	paths[1][1]->tab[0] = 10;

	display_besttab(paths);
	display_allmoves(&e, paths, 0);
	free_env(&e);
	return (0);
}
