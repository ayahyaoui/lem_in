/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:40:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 17:02:22 by emuckens         ###   ########.fr       */
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
		if (ft_strequ(str, (char *)tmp->content))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int		is_number(char *name)
{
	char *s;

	s = name;
	while (*s)
		if (ft_isdigit(*s++) == 0)
			return (0);
	return (1);
}

/*
** Check value of room name and coordinates
** Input: room name and coordinates read on stdin
** Returns true if coordinates are numerical and if name has no '-' to avoid
** confusion with tube instructions | false otherwise
*/

static int		valid_room_input(ENV *e, char *name, char *x, char *y)
{
	int		ignore;

	if (!is_number(x) || !is_number(y))
		e->err = ERR_COORD;
	else if (sep(name, &ignore) == '-')
		e->err = ERR_ROOM_CONF;
	else
		return (1);
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
	static char	ref[NB_COMMANDS][7] = {"##START", "##END"};

	if (!(room = (t_room *)ft_memalloc(sizeof(t_room))) && (e->err = ERR_ALLOC))
		return (NULL);
	room->name = ft_strdup(name);
	room->x = ft_atoi(x);
	room->y = ft_atoi(y);
	ft_bzero(room->mark, sizeof(room->mark));
	tmp = e->ins->special;
	while (tmp && tmp->content_size == UNDEALT)
	{
		i = -1;
		while (++i < NB_COMMANDS)
		{
			if (ft_strequ(((t_special *)(tmp->content))->str, ref[i]))
				room->mark[i] = i;
		}
		((t_special *)(tmp->content))->dest[0] = ROOM;
		((t_special *)(tmp->content))->dest[1] = ft_lstsize(e->ins->rooms);
		tmp->content_size = DEALT;
		tmp = tmp->next;
	}
//	ft_printf("check room content: name = %s x = %d y = %d mark0 = %d mark1 = %d\n", room->name, room->x, room->y, room->mark[0], room->mark[1]);
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

	if (str[1] && str[2] && !str[3])
	{
		if (!valid_room_input(e, str[0], str[1], str[2]))
			return (INVALID_INPUT);
		if (is_dup(e->ins->rooms, str[0]) && (e->err = ERR_DUP))
			return (INVALID_INPUT);
		details = create_room(e, str[0], str[1], str[2]);	
		room = ft_lstnew(details, sizeof(details));
		if (!room && (e->err = ERR_LIB))
			return (INVALID_INPUT);
		ft_lstadd(&e->ins->rooms, room);
		return (VALID_INPUT);
	}
	return (INVALID_INPUT && (e->err = ERR_ROOM));
}
