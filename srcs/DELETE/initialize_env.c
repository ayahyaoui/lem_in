/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:50:19 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 19:13:13 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

/*
** Set up environment
** Return error code if malloc error, else return 1
*/

int			set_env(ENV *e)
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
	e->max_paths = -1;
	e->nb_line = 0;
	return (1);
}
