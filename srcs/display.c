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

void		display_adj_mtrx(ENV *e, char **tab, int size)
{
	int	i;
	int	j;	

	i = -1;
	ft_printf("display adj mtrx\n");
	ft_printf("\t | ", i);
	while (++i < size)
		ft_printf("%s\t", e->ins->room[i].name);
	ft_printf("\n");
	j = -1;
	while (++j < size)
	{
		i = -1;
		ft_printf("%s\t | ", e->ins->room[j].name);
		while (++i < size) 
			ft_printf("%d\t", tab[j][i]);
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

int		ant_in_room(ENV *e, t_tab ***paths, int ant, int room)
{
	int i;

	i = -1;
	if (room == e->graphe->end)
		return (0);
	while (++i < ant)
	{
		if (e->ants[i][0] != -2 && paths[e->ants[i][0]] && paths[e->ants[i][0]][e->ants[i][1]])
		{
			if (e->ants[i][0] != -2 && paths[e->ants[i][0]][e->ants[i][1]]->tab[e->ants[i][2]] == room)
				return (1);
		}
	}
	return (0);

}

void		move_next_room(ENV *e, t_tab ***paths , int comb)
{
//	int i;
	int j;
	int ant;

	(void)comb;
	ant = 0;
	while (e->ants[ant])
		++ant;
	j = -1;
	while (++j < ant)
	{
		if (e->ants[j][0] != -2 && e->ants[j][2] + 1 < paths[e->ants[j][0]][e->ants[j][1]]->length)
		{
			if (!ant_in_room(e, paths, j, paths[e->ants[j][0]][e->ants[j][1]]->tab[e->ants[j][2] + 1]))
				e->ants[j][2] += 1;
		}
	}
}

void		ant_enter_path(ENV *e, t_tab ***paths, int comb)
{
	int i;
	int ant;

	while (comb >= 0)
	{
		i = 0;
		ant = 0;
		while (paths[comb][i])
		{
			while (e->ants[ant])
				++ant;
			if (paths[comb][i]->tab[0] && ant < e->ins->nb_ants && !ant_in_room(e, paths, ant, paths[comb][i]->tab[1]))
			{
				e->ants[ant]= (int *)ft_memalloc(sizeof(int) * 3);
				e->ants[ant][0] = comb;
				e->ants[ant][1] = i;
				e->ants[ant][2] = 1;
				--paths[comb][i]->tab[0];
			}
			++i;
		}
		--comb;
	}
}


int		display_travelling(ENV *e, t_tab ***paths)
{
	int ant;
	int arrived;

	ant = -1;
	arrived = 0;
	while (++ant < e->ins->nb_ants && e->ants[ant])
	{	
		if (e->ants[ant][0] != -2 && paths[e->ants[ant][0]][e->ants[ant][1]]->tab[e->ants[ant][2]] == e->graphe->end)
		{
			if (e->options & OPT_COLOR)
				ft_printf("{CYAN}L%d-%s{EOC} ", ant + 1, e->ins->room[paths[e->ants[ant][0]][e->ants[ant][1]]->tab[e->ants[ant][2]]].name);
			else
				ft_printf("L%d-%s ", ant + 1, e->ins->room[paths[e->ants[ant][0]][e->ants[ant][1]]->tab[e->ants[ant][2]]].name);
			e->ants[ant][0] = -2;
			++arrived;
		}
		else if (e->ants[ant][0] != -2)
			ft_printf("L%d-%s ", ant + 1, e->ins->room[paths[e->ants[ant][0]][e->ants[ant][1]]->tab[e->ants[ant][2]]].name);
		else
			++arrived;
	
	}
	ft_printf("\n");
	return (arrived);
}



void		display_allmoves(ENV *e, t_tab ***paths, int arrived)
{
	int nb_comb;
	int	high_comb;

	nb_comb = 0;
	while (paths[nb_comb])
		++nb_comb;
	high_comb = nb_comb;
	e->ants = (int **)ft_memalloc(sizeof(int *) * (e->ins->nb_ants + 1));
	while (arrived < e->ins->nb_ants)
	{
		move_next_room(e, paths, nb_comb);
		ant_enter_path(e, paths, high_comb - 1);
		arrived = display_travelling(e, paths);
		nb_comb = high_comb;
	}
}

