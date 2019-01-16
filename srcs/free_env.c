/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 19:10:50 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 23:02:39 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Delete anthill
*/

static void		del_anthill(t_list **l)
{
	t_list *tmp;
	t_list *lcpy;

	lcpy = *l;
	while (lcpy)
	{
		tmp = lcpy;
		lcpy = lcpy->next;
		ft_memdel((void **)&(tmp->content));
		ft_memdel((void **)&tmp);
	}
}

/*
** Delete all room content
*/

static void		del_rooms(ENV *e, t_room **room)
{
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = *room;
	while ((unsigned int)i < e->graphe->nb_rooms && tmp && tmp[i].name)
	{
		ft_strdel(&tmp[i].name);
		ft_memdel((void **)&tmp[i]);
		++i;
	}
	ft_memdel((void **)room);
}

static void		free_besttab(t_tab ***best_tab)
{
	int i;
	int j;

	if (best_tab)
	{
		i = -1;
		while (best_tab[++i])
		{
			j = -1;
			while (best_tab[i][++j])
			{
				ft_memdel((void**)(&(best_tab[i][j]->tab)));
				ft_memdel((void**)&best_tab[i][j]);
			}
			ft_memdel((void**)(&best_tab[i]));
		}
		ft_memdel((void**)&best_tab);
	}
}

/*
** Free environement at end: rooms, graphe, commands, instructions, anthill
*/

void			free_env(ENV *e)
{
	del_rooms(e, &e->ins->room);
	free_graphe(e->graphe);
	free_besttab(e->all_paths);
	if (e->ins)
	{
		ft_free_inttab(&e->ins->commands, e->ins->nb_commands);
		ft_memdel((void **)&e->ins);
	}
	del_anthill(&e->anthill);
}
