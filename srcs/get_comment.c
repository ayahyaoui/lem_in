/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:01:15 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/04 19:55:32 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

void			c_start(ENV *e, void **item, int index)
{
	(void)item;
	e->graphe->start = index;
}

void			c_end(ENV *e, void **item, int index)
{
	(void)item;
	e->graphe->end = index;
}

/*
** ### Check comment format, marks start and end for following room reading
** Input: line read on stdin, not broken up
** Prints comment and returns true if comment OK | false otherwise
*/

void			apply_commands(ENV *e)
{
	static void	 (*f[NB_COMMANDS])(ENV *e, void **item, int index)
		= {&c_start, &c_end}; 
	int			index;

	index = 0;
	while (index < e->ins->nb_commands)
	{
		if (e->ins->commands_dest[index][0] == ROOM)
			f[index](e, NULL, e->ins->commands_dest[index][1]);
		++index;
	}
//	ft_printf("start in %d end in %d\n", e->graphe->start, e->graphe->end);
}

void			link_command(ENV *e, int type, int index)
{
	static int	linked;

	while (e->ins->commands[linked] && linked < e->ins->nb_commands)
	{
		e->ins->commands_dest[linked] = (int *)ft_memalloc(sizeof(int) * 2);
		e->ins->commands_dest[linked][0] = type;
		e->ins->commands_dest[linked][1] = index;
		++linked;
	}
}

/*
** Checks if comment or command, adds latter to command list
** Returns 0 if comment or command, to skip significant input treatment
*/

int				get_command(ENV *e, char *str)
{
	static int	index;
	static char	ref[NB_COMMANDS][8] = {"##START", "##END"};
	int			i;

	i = 0;
	while (i < NB_COMMANDS)
	{
		if (ft_strequ(str, ref[i]))
			break;
		++i;
	}
	if (i == NB_COMMANDS)
		return (0);
	e->ins->commands[index] = ft_strdup(str);
	++index;
	return (i);
}
