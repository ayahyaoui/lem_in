/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:04:49 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/04 20:01:32 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

void		display_adj_mtrx(int **tab, int size)
{
	int	i;
	int	j;	

	i = -1;
	ft_printf("\t | ", i);
	while (++i < size)
		ft_printf("%d ", i);
	ft_printf("\n");
	j = -1;
	while (++j < size)
	{
		i = -1;
		ft_printf("%d\t | ", j);
		while (++i < size) 
			ft_printf("%d ", tab[j][i]);
		ft_printf("\n");
	}

}


void		display_anthill(t_list *anthill)
{
	t_list *tmp;

	tmp = anthill;
	while (tmp)
	{
		ft_printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}


t_list	*ft_lstval(t_list *l, int index)
{
	int i;
	t_list *tmp;

	i = 0;
	tmp = l;
	while (i < index)
	{
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}

/*

char		**room_names(t_list *l, int nbrooms, int **paths, int nbpaths)
{
	char	**names;
	int	i;
	int	j;
	
	i = -1;
	names = (char **)ft_memalloc(sizeof(char *) * nbrooms);
	while (++i < nbpaths)
	{
		j = 1;
//		ft_printf("val in tab = %d\n", paths[i][j]);
		while (paths[i][j] != -1)
		{	
//			ft_printf("name stored in i = %d j = %d\n", i, j);
		//	ft_printf("retrieve name %s\n", ((t_room *)ft_lstval(l, paths[i][j])->content)->name);
			names[paths[i][j]] = ft_strdup(((t_room *)ft_lstval(l, paths[i][j])->content)->name);
		//	ft_printf("check name = %s\n", names[paths[i][j]]);
			++j;
		}
	}
	return (names);
}
*/

void		print_movestab(int **ants, int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
	j = -1;
		while (++j < ants[i][0] + 1)
			ft_printf("%d ", ants[i][j]);
		ft_printf("\n");
	}
}


void		move_next_room(int **paths, int ***ants, int nb_paths, int turn)
{
	int i;
	int ant;

	i = -1;
	while (++i < nb_paths)
	{
		ant = (*ants)[i][0];
		while (ant > 1)
		{
			(*ants)[i][ant] = (*ants)[i][ant - 1];
			--ant;
		}
		if (paths[i][turn] != -1 && (*ants)[i][2] != -1)
			(*ants)[i][1] = paths[i][turn];
		else
			(*ants)[i][1] = -1;
			
	}
//	print_movestab(*ants, nb_paths);
}


int		display_travelling(ENV *e, int turn)
{
	int comb;
	int path;
	int j;
//	int ant;
	int arrived;

	j = 0;
//	ant = 1;
	arrived = 0;
//	ft_printf("turn = %d\n", turn);
	while (++j < turn)
	{
		comb = -1;
		while (e->ants[comb])
		{
			path = 0;
			while (e->ants[comb][path])
			{
//			while (++i < e->nb_paths)
//			{
//			ft_printf("j = %d ants i 0 = %d\n", j, ants[i][0]);
				if (j <= e->ants[comb][path][0] && arrived < ((t_input *)e->ins)->nb_ants)
				{
//					ft_printf("room code = %d for ant # %d\n", ants[i][j], ant);
					if (e->ants[comb][path][j] != -1)
						ft_printf("L%d-%s ", ant, e->ins->room[e->ants[comb][path][j]]);
					else
						++arrived;
				}
				++path;	
//			++ant;
			}
			++comb;
		}
	}

	ft_printf("\n");
//	ft_printf("arrived = %d\n", arrived);
	return (arrived);
}

int		ant_in_room(int comb, int path, int room)
{
	int i;
	int j;

	i = 0;
	while (e->ants[i])
	{
		if (i != comb)
		{
			j = 0;
			while (e->ants[i][j])
			{
				if (ft_isintab(e->ants[i][j].tab, room))
					return (1);
				++j;
			}
		}
		++i;
	}

}



void		display_moves(ENV *e, t_tab *paths, int total, int comb)
{
	int **ants;
	int	i;
	int 	j;
	int	nb_paths;

	nb_paths = 0;
	while (paths[nb_paths])
		++nb_paths;
	int turn;
	(void)total;
	i = -1;
	turn = 2;
	e->ants[comb] = (int **)ft_memalloc(sizeof(int *) * nb_paths);	
	while (++i < nb_paths)
	{
		j = 0; // ancienemment 1
		e->ants[comb][i] = (int *)malloc(sizeof(int) * (paths[i].tab[0] + 1));
		e->ants[comb][i][0] = paths[i].tab[0];
		e->ants[comb][i][1] = paths[i].tab[1];
		while (++j < paths[i].tab[0]) // anciennement paths[i][0] + 1
			e->ants[comb][i][j] = -1;
	}
	// ajuster a nouveau param 
//	print_movestab(ants, size);
	while (display_travelling(e, turn) < total)
	{
		move_next_room(paths, &ants, nb_paths, turn);
		++turn;
	}
}

void		display_allmoves(ENV *e, t_tab ***paths, int arrived)
{
	int nb_comb;

	nb_comb = 0;
	while (paths[nb_comb])
		++nb_comb;
	e->ants = (int ***)ft_memalloc(sizeof(int *) * nb_comb);

}

