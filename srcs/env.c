/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:50:19 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 20:23:58 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

/*
** Delete anthill
*/

void		del_anthill(t_list *l)
{
	t_list *tmp;
	
	while (l)
	{
		tmp = l;
		ft_memdel((void **)tmp);
		l = l->next;
	}
}

/*
** Delete all room content
*/

void		del_rooms(ENV *e, t_room **room)
{
	t_room *tmp;
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

/*
** Free environement at end: rooms, graphe, commands, instructions, anthill
*/

void		free_env(ENV *e)
{
	del_rooms(e, &e->ins->room);
	free_graphe(e->graphe);
	ft_free_inttab(&e->ins->commands, e->ins->nb_commands);	
	ft_memdel((void **)&e->ins);
	del_anthill(e->anthill);
}

/*
** Set up environment
** Return error code if malloc error, else return 1
*/

int		set_env(ENV *e)
{
	if (!(e->ins = (t_input *)ft_memalloc(sizeof(t_input))))
		return (ERR_ALLOC);
	if (!(e->graphe = (t_graphe *)ft_memalloc(sizeof(t_graphe))))
		return (ERR_ALLOC);
	e->ins->nb_ants = 0;
	e->anthill = NULL;
	e->options = 0;
	e->ins->room = NULL;
	e->ins->commands = NULL;
	e->turns = 0;
	e->ins->nb_commands = 0;
	e->graphe->map = NULL;
	e->graphe->start = -1;
	e->graphe->end = -1;
	return (1);
}
