/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:50:19 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/04 20:01:38 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_strtab(char ***tab)
{
	char **tmp;

	if (!*tab)
	{
		ft_printf("coucou\n");
		return ;
	}
	tmp = *tab;
	while (tmp && *tmp)
	{
		ft_strdel(tmp);
		++tmp;
	}
	ft_memdel((void **)tab);
}

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


void		free_inttab(int ***tab, int size)
{
	int **tmp;
	int i;

	i = -1;
	if (!*tab)
		return ;
	tmp = *tab;
	while (++i < size)
	{
		ft_memdel((void **)tmp);
		++tmp;
	}
	ft_memdel((void **)tab);
}


void		free_env(ENV *e)
{
	free_graphe(e->graphe);
	free_strtab(&e->ins->room);
	free_strtab(&e->ins->commands);
	free_inttab(&e->ins->commands_dest, e->ins->nb_commands);	
	ft_memdel((void **)&e->ins);
	del_anthill(e->anthill);
}

int		set_env(ENV *e)
{
	if (!(e->ins = (t_input *)ft_memalloc(sizeof(t_input))))
		return (ERR_ALLOC);
	if (!(e->graphe = (t_graphe *)ft_memalloc(sizeof(t_graphe))))
		return (ERR_ALLOC);
	e->ins->nb_ants = 0;
	e->anthill = NULL;
	e->options = 2;
	e->ins->room = NULL;
	e->ins->commands = NULL;
	e->ins->nb_commands = 0;
	e->graphe->start = -1;
	e->graphe->end = -1;
	return (1);
}
