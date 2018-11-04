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

	tmp = *tab;
	while (tmp && *tmp)
	{
		ft_memdel((void **)tmp);
		++tmp;
	}
	ft_memdel((void **)tab);
}
/*
void		del_rooms(t_list *l)
{
	t_list *tmp;
	
	while (l)
	{
		tmp = l;
		ft_memdel((void **)&((t_room *)l->content)->name);
		ft_memdel((void **)&l->content);
		ft_memdel((void **)tmp);
		l = l->next;
	}

}
*/
int		set_env(ENV *e)
{
	if (!(e->ins = (t_input *)ft_memalloc(sizeof(t_input))))
		return (ERR_ALLOC);
	if (!(e->graphe = (t_graphe *)ft_memalloc(sizeof(t_graphe))))
		return (ERR_ALLOC);
	e->ins->nb_ants = 0;
	e->anthill = NULL;
	e->options = 2;
	e->ins->nb_commands = 0;
	return (1);
}
