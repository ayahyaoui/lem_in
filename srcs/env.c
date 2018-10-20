/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:50:19 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 02:10:06 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		set_env(ENV *e)
{
	if (!(e->ins = (t_input *)ft_memalloc(sizeof(t_input))))
	{
		e->err = ERR_ALLOC;
		return (0);
	}
	if (!(e->graphe = (t_graphe *)ft_memalloc(sizeof(t_graphe))))
	{
		e->err = ERR_ALLOC;
		return (0);
	}
	e->ins->nb_ants = 0;
	e->options = 2;
	e->err = NO_ERR;
	e->graphe->start = -1;
	e->graphe->end = -1;
	
	return (1);
}
