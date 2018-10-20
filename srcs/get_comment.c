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

void		ft_swaprooms(t_room **r1, t_room **r2)
{
	char *tmp;

	ft_swap(&(*r1)->x, &(*r2)->x);
	ft_swap(&(*r1)->y, &(*r2)->y);
	tmp = (*r1)->name;
	(*r1)->name = (*r2)->name;
	(*r2)->name = tmp;
}

void			c_start(ENV *e, void **item, int index)
{
	t_list	*room;
	int		i;

	(void)item;
	i = -1;
	room = e->ins->rooms;
	while (i < index)
		room = room->next;
	ft_swaprooms(((t_room**)(&e->ins->rooms->content), (t_room **)(&room->content)));
	ft_printf("new first room content: name = %s x = %d y = %d\n", ((t_room *)(e->ins->rooms->content))->name, ((t_room *)(e->ins->rooms->content))->x, ((t_room *)(e->ins->rooms->content))->y);
}

/*
** ### Check comment format, marks start and end for following room reading
** Input: line read on stdin, not broken up
** Prints comment and returns true if comment OK | false otherwise
*/

void			apply_commands(ENV *e)
{
	static void	 (*f[NB_COMMANDS])(ENV *e, void **item, int index)
		= {&c_start, &c_start}; 
	t_list		*command;
	t_list		*dest;
	int			i;

	dest = e->ins->rooms;
	command = e->ins->special;
	while (command)
	{
		if (((t_special *)(command->content))->dest[0] == ROOM)
		{
				ft_printf("add command type = %d index = %d\n", ((t_special *)(command->content))->dest[0],
				((t_special *)(command->content))->dest[1]);
			i = -1;
			while (++i < ((t_special *)(command->content))->dest[1])
				dest = dest->next;
			f[((t_special *)(command->content))->index](e, (void **)&dest, -1);
		}
		command = command->next;
	}
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
