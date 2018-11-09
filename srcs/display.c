/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:04:49 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/09 16:22:05 by emuckens         ###   ########.fr       */
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

int		ant_in_room(ENV *e, int comb, int room)
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
				if (ft_isintab(e->ants[i][j], e->ants[i][j][0], room))
					return (1);
				++j;
			}
		}
		++i;
	}
	return (0);

}

void		move_next_room(ENV *e, t_tab ***paths , int comb)
{
	int i;
	int j;
	int ant;

	i = -1;
	ft_printf("in move next room, comb = %d\n", comb);
	while (paths[comb][++i])
//	while (++i < nb_paths)
	{
		ant = e->ants[comb][i][0] - 1;
		ft_printf("nb ants = %d\n", ant);
		while (ant > 1)
		{
			ft_printf("ant = %d check if room %d already occupied\n", ant, e->ants[comb][i][ant - 1]);
			if (e->ants[comb][i][ant - 1] != - 1 && !(ant_in_room(e, comb, e->ants[comb][i][ant - 1])))
			{
				ft_printf("move ant from room: before, ant #%d in room %d - ", ant, e->ants[comb][i][ant]);
				e->ants[comb][i][ant] = e->ants[comb][i][ant - 1];
				ft_printf("after: room %d\n", e->ants[comb][i][ant]); 
			}
			--ant;
		}
		if (e->ants[comb][i][e->ants[comb][i][0] - 1] == -1)
		{
			j = 1;
			while (paths[comb][i]->tab[j] == -1 /*&& j < paths[comb][i]->length*/)
			{
				++j;
			}
			if (!(ant_in_room(e, comb, paths[comb][i]->tab[j])))
			{
			   e->ants[comb][i][1] = paths[comb][i]->tab[j];
		   	   paths[comb][i]->tab[j] = -1;	   
			}
		}
//		if (paths[comb][i][turn] != -1 && e->ants[comb][i][1] != -1
//				&& !(ant_in_room(comb, i, paths[comb][i][turn])
//			(*ants)[i][1] = paths[i][turn];
//		else
//			(*ants)[i][1] = -1;
			
	}
//	print_movestab(*ants, nb_paths);
}


int		display_travelling(ENV *e)
{
	int comb;
	int path;
	int j;
	int ant;
	int arrived;

	j = 0;
	ant = 1;
	arrived = 0;
//	ft_printf("turn = %d\n", turn);
//	while (++j < turn)
//	{
		comb = -1;
		while (e->ants[++comb])
		{
			ft_printf("go on next (smaller) comb\n");
			path = 0;
			while (e->ants[comb][path])
			{
				ft_printf("all ants on path: ");
				for (int k = 0; k < e->ants[comb][path][0]; ++k)
					ft_printf("%d ", e->ants[comb][path][k]);
				ft_printf("\n");
				ft_printf("j = %d ants i 0 = %d\n", j, e->ants[comb][path][0]);
				j = 0;
				while (j < e->ants[comb][path][0]/* && arrived < ((t_input *)e->ins)->nb_ants*/)
			
				{
					ft_printf("room code = %d for ant # %d, end code = %d\n", e->ants[comb][path][j], ant, e->graphe->end);
//					ft_printf("room code = %d for ant # %d\n", ants[i][j], ant);
					if (e->ants[comb][path][j] == e->graphe->end)
						++arrived;
					if (e->ants[comb][path][j] != -1)
						ft_printf("L%d-%s ", ant, e->ins->room[e->ants[comb][path][j]].name);
					++j;
				++ant;
				}
				++path;	
			}
		}
	ft_printf("\n");
	ft_printf("arrived = %d\n", arrived);
	return (arrived);
}


/*

void		display_moves(ENV *e, t_tab ***paths, int comb, int *arrived)
{
	int	i;
	int 	j;
	
	i = -1;
//	print_movestab(ants, size);
	while (display_travelling(e, turn) < total)
	{
		move_next_room(paths, &ants, nb_paths, turn);
		++turn;
	}
}
*/
void		set_ants(ENV *e, t_tab ***paths, int nb_comb)
{
	int	comb;
	int nb_paths;
	int	i;
	int j;

	comb = -1;
	while (++comb < nb_comb)
	{
		nb_paths = 0;
		while (paths[comb][nb_paths])
		{
			ft_printf("check tab\n");
			ft_print_inttab(paths[comb][nb_paths]->tab, paths[comb][nb_paths]->length , '|');
			++nb_paths;
		}
		ft_printf("nb paths = %d\n", nb_paths);
		e->ants[comb] = (int **)ft_memalloc(sizeof(int *) * (nb_paths + 1));
		comb = 0;
		i = -1;
		while (paths[comb][++i])
		{
			j = 0;
			e->ants[comb][i] = (int *)malloc(sizeof(int) * (paths[comb][i]->tab[0] + 1));
			e->ants[comb][i][0] = paths[comb][i]->tab[0];
			e->ants[comb][i][e->ants[comb][i][0] - 1] = -1;
			while (++j < paths[comb][i]->tab[0])
				e->ants[comb][i][j] = -1;
		}
	}

}

void		display_allmoves(ENV *e, t_tab ***paths, int arrived)
{
	int nb_comb;
	int	high_comb;

	nb_comb = 0;
	while (paths[nb_comb])
		++nb_comb;
	ft_printf("nb comb: %d\n", nb_comb);
	high_comb = nb_comb;
	e->ants = (int ***)ft_memalloc(sizeof(int *) * (nb_comb + 1));
	set_ants(e, paths, nb_comb);	
	while (arrived < e->ins->nb_ants)
	{
		display_besttab(paths);
		ft_printf("arrived = %d total ants = %d, nb_comb = %d\n", arrived, e->ins->nb_ants, nb_comb);
		while (--nb_comb >= 0 && arrived < e->ins->nb_ants)
		{
			arrived = display_travelling(e);
			move_next_room(e, paths, nb_comb);
//			display_moves(e, paths, nb_comb, &arrived);
//			--nb_comb;
		}
		nb_comb = high_comb;
	}
}

