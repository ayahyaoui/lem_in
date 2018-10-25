/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:01:15 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/21 01:40:42 by emuckens         ###   ########.fr       */
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
	t_list		*command;
	t_list		*dest;
	int			index;

	dest = e->ins->rooms;
	command = e->ins->special;
	while (command)
	{
		if (((t_special *)(command->content))->dest[0] == ROOM)
		{	
			index = ((t_special *)command->content)->dest[1];
			f[((t_special *)(command->content))->index](e, (void **)&dest, index);
		}
		command = command->next;
	}
	ft_printf("start in %d end in %d\n", e->graphe->start, e->graphe->end);
}

void			link_command(ENV *e, int type, int index)
{
	static char	ref[NB_COMMANDS][8] = {"##START", "##END"};
	t_list *tmp;
	int		i;

	tmp = e->ins->special;
	while (tmp && ((t_special *)(tmp->content))->status == UNDEALT)
	{
		i = 0;
		while (++i <= NB_COMMANDS)
		{
			if (ft_strequ(((t_special *)(tmp->content))->str, ref[i]))
			{
				((t_special *)(tmp->content))->dest[0] = type;
				((t_special *)(tmp->content))->dest[1] = index;
			}
		}
		tmp->content_size = DEALT;
		tmp = tmp->next;
	}
}

/*
** Checks if comment or command, adds latter to command list
** Returns 0 if comment or command, to skip significant input treatment
*/

int				get_command(ENV *e, char *str)
{
	static char	ref[NB_COMMANDS][8] = {"##START", "##END"};
	t_special	*details;
	t_list		*new;
	int			i;

	i = -1;
	if (str[1] != '#')
		return (1);
	if (!(details = (t_special *)ft_memalloc(sizeof(details))))
		return (ERR_ALLOC);
	details->index = -1;
	while (++i < NB_COMMANDS)
		if (ft_strequ(str, ref[i]))
			details->index = i;
	ft_printf("details index = %d\n", details->index);
	if (details->index >= 0)
	{
		details->str = ft_strdup(str);
		details->status = UNDEALT;
		new = ft_lstnew(details, sizeof(*details));
		ft_lstadd(&e->ins->special, new);
		return (1);
	}
	else
		ft_memdel((void **)details);
	return (0);
}
