/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:40:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 22:59:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <stdlib.h>

/*
** Input: room name
** Returns true if name has already been stored | false otherwise
*/

static int		is_dup(t_list *l, char *str)
{
	t_list *tmp;

	tmp = l;
	while (tmp)
	{
		if (ft_strequ(str, ((t_room *)(tmp->content))->name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
** ### Fill room name, coordinates and special actions 
** Input: str name coordinates from input
** Scans comments list, finds all undealt comments, stores significant ones and
** marks them as dealt (ignores unkown comments)
** Returns room link to add to list
*/

static t_room	*create_room(ENV *e, char *name, char *x, char *y)
{
	t_room	*room;
	t_list	*tmp;
	int		i;
	static char	ref[NB_COMMANDS + 1][8] = {"##START", "##END"};

	if (!(room = (t_room *)ft_memalloc(sizeof(t_room))) && (e->err = ERR_ALLOC))
		return (NULL);
	room->name = ft_strdup(name);
	room->x = ft_atoi(x);
	room->y = ft_atoi(y);
	ft_bzero(room->mark, sizeof(room->mark));
	tmp = e->ins->special;
	while (tmp && ((t_special *)(tmp->content))->status == UNDEALT)
	{
		i = -1;
		while (++i < NB_COMMANDS)
		{
			if (ft_strequ(((t_special *)(tmp->content))->str, ref[i]))
				room->mark[i] = 1;
		}
		((t_special *)(tmp->content))->dest[0] = ROOM;
		((t_special *)(tmp->content))->dest[1] = ft_lstsize(e->ins->rooms);
		tmp->content_size = DEALT;
		tmp = tmp->next;
	}
	ft_printf("{FD!}|check room content: name = %s x = %d y = %d mark0 = %d mark1 = %d\n", &e->fd, room->name, room->x, room->y, room->mark[0], room->mark[1]);
	return (room);
}

/*
** ### Check room info, store in list, # mark start and end
** Input: line read on stdin, broken up by space
** Returns true if room valid and successfully stored | false otherwise
*/

int				get_room(ENV *e, char **str)
{
	t_room		*details;
	t_list		*room;
	int			ret;

	ret = NO_ERR;

	if (str[1] && str[2] && !str[3])
	{
		if (!is_number(str[1]) || !is_number(str[2]))
			return (ERR_COORD);
		if (is_dup(e->ins->rooms, str[0]))
			return (ERR_DUP);
		details = create_room(e, str[0], str[1], str[2]);	
		if (!(room = ft_lstnew(details, sizeof(*details))))
			return (ERR_LIB);
		ft_lstaddend(&e->ins->rooms, room);
		return (NO_ERR);
	}
	return (ERR_ROOM);
}
