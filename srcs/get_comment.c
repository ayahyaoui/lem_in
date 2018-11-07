/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:01:15 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/07 15:05:43 by emuckens         ###   ########.fr       */
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

int			apply_commands(ENV *e)
{
	static void	 (*f[NB_COMMANDS])(ENV *e, void **item, int index)
		= {&c_start, &c_end}; 
	int			index;
	
	index = -1;
	if (!e->graphe->map)
		return (ERR_NOTUBE);
	while (++index < e->ins->nb_commands)
	{
		if (!e->ins->commands[index])
			break;
		if (e->ins->commands[index][1] == ROOM)
			f[e->ins->commands[index][0]](e, NULL, e->ins->commands[index][2]);
	}
//	ft_printf("start = %d end = %d\n", e->graphe->start, e->graphe->end);
	if (e->graphe->start == -1)
		return (ERR_START);
	if (e->graphe->end == -1)
		return (ERR_END);
	return (NO_ERR);

}

void			link_command(ENV *e, int type, int index)
{
	static int	linked;
	
//	ft_printf("linked = %d nb commands = %d\n", linked, e->ins->nb_commands);
	while (e->ins->commands[linked] && linked < e->ins->nb_commands)
	{
		e->ins->commands[linked][1] = type;
		e->ins->commands[linked][2] = index;
//	ft_printf("commands[linkded] [0] = %d\n", e->ins->commands[linked][0]);
//	ft_printf("commands[linkded] [1] = %d [2] = %d\n", type, index);
		++linked;
	}
}

/*
** Checks if comment or command, adds latter to command list
** Returns 0 if comment or command, to skip significant input treatment
*/

int				get_command(ENV *e, char *str, int option)
{
	static int	index;
	static char	ref[NB_COMMANDS][8] = {"##start", "##end"};
	int			i;

	i = -1;
	while (++i < NB_COMMANDS)
		if (ft_strequ(str, ref[i]))
		{
//			ft_printf("string: %s match found! option = %d\n", str, option);
			if (option == 0)
				return (1);
			break;
		}
	if (i == NB_COMMANDS) 
		return (0);
//	ft_printf("i = %d index = %d\n", i, index);
	e->ins->commands[index] = (int *)ft_memalloc(sizeof(int) * 3);
	e->ins->commands[index][0] = i;
//	ft_printf("commands index 0 = %d\n", e->ins->commands[index][0]);
	if (index < NB_COMMANDS)
		++index;
	return (i);
}
