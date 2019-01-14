/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:40:04 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 22:35:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <stdlib.h>

/*
** Input: room name
** Returns true if name has already been stored | false otherwise
*/

int		is_dup(ENV *e, char *str, int max_index)
{
	int i;

	i = -1;
	while (++i < max_index)
		if (ft_strequ(str, e->ins->room[i].name))
			return (1);
	return (0);
}

/*
** Scans anthill and stores room names in char **tab, while checking if
** duplicate room names
** link with commands if command(s) detected and unlinked
** returns err code if error, 0 if success
*/

int		store_rooms(ENV *e)
{
	int	i;
	t_list	*tmp;
	char	**split;

	i = 0;
	tmp = e->anthill;
	e->ins->room = (t_room *)ft_memalloc(sizeof(t_room) * (e->graphe->nb_rooms + 1));
	e->ins->commands = (int **)ft_memalloc(sizeof(int *) * (e->ins->nb_commands + 1));
	if (!e->ins->room || !e->ins->commands)
		return (ERR_ALLOC);
	while (((char *)tmp->content)[0] == '#')
		tmp = tmp->next;
	while ((tmp = tmp->next) && ((unsigned int)i < e->graphe->nb_rooms))
	{
		if (((char *)tmp->content)[0] != '#')
		{
			split = ft_strsplit((char *)tmp->content, ' ');
			e->ins->room[i].name = (char *)ft_strdup(split[0]);
			ft_4vinit(&e->ins->room[i].pos, ft_atoi(split[1]), ft_atoi(split[2]), 0);
			ft_free_strtab(&split);
			link_command(e, ROOM, i);
			if (is_dup(e, e->ins->room[i].name, i))
				return (ERR_DUP);
			++i;
		}
		else if (((char *)tmp->content)[1] == '#')
			get_command(e, ((char *)tmp->content), 1);
	}
	return (NO_ERR);
}

/*
** ### Check room info, store in list, # mark start and end
** Input: line read on stdin, broken up by space
** Returns true if room valid and successfully stored | false otherwise
*/

int				get_room(ENV *e, char **str)
{
	if (str[1] && str[2] && !str[3])
	{
		if (!is_number(str[1]) || !is_number(str[2]))
			return (ERR_COORD);
		if (ft_beyond_limiti(str[1]) || ft_beyond_limiti(str[2]))
			return (ERR_INTMAX);
		if (str[0][0] == 'L')
			return (ERR_ROOM_CHAR);
		++e->graphe->nb_rooms;
		return (NO_ERR);
	}
	return (ERR_ROOM);
}
