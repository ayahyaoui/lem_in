/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:40:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/21 01:41:09 by emuckens         ###   ########.fr       */
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
		if (!(details = (t_room *)ft_memalloc(sizeof(t_room))))
			return (ERR_ALLOC);
		details->name = ft_strdup(str[0]);
		details->x = ft_atoi(str[1]);
		details->y = ft_atoi(str[2]);
		if (!(room = ft_lstnew(details, sizeof(*details))))
			return (ERR_LIB);
		ft_lstaddend(&e->ins->rooms, room);
		link_command(e, ROOM, ft_lstsize(e->ins->rooms));
		return (NO_ERR);
	}
	return (ERR_ROOM);
}
