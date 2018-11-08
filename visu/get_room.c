/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:40:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 16:36:15 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdlib.h>

/*
** Input: room name
** Returns true if name has already been stored | false otherwise
*/

int		is_dup(VISU *v, char *str, int max_index)
{
	int i;

	i = -1;
	while (++i < max_index)
		if (ft_strequ(str, v->ins->room[i].name))
			return (1);
	return (0);
}

/*
** Scans anthill and stores room names in char **tab, while checking if
** duplicate room names
** returns err code if error, 0 if success
*/

int		store_rooms(VISU *v)
{
	int	i;
	t_list	*tmp;
	char	**split;

	i = 0;
	tmp = v->anthill;
	if (!(v->ins->room = (t_room *)ft_memalloc(sizeof(t_room) * (v->graphe->nb_rooms + 1))))
		return (ERR_ALLOC);
	if (!(v->ins->commands = (int **)ft_memalloc(sizeof(int *) * (v->ins->nb_commands + 1))))
		return (ERR_ALLOC);
	while (((char *)tmp->content)[0] == '#')
		tmp = tmp->next;
	while ((tmp = tmp->next) && ((unsigned int)i < v->graphe->nb_rooms))
	{
		if (((char *)tmp->content)[0] != '#')
		{
			split = ft_strsplit((char *)tmp->content, ' ');
			v->ins->room[i].name = (char *)ft_strdup(split[0]);
			ft_4ivinit(&v->ins->room[i].pos, ft_atoi(split[1]), ft_atoi(split[2]), rand() % 100); // put z to random for 3D
			ft_printf("store room %s with coord %d %d %d\n", v->ins->room[i].name, v->ins->room[i].pos.x, v->ins->room[i].pos.y, v->ins->room[i].pos.z);
			free_strtab(&split);
			link_command(v, ROOM, i);
			if (is_dup(v, v->ins->room[i].name, i))
				return (ERR_DUP);
			++i;
		}
		else if (((char *)tmp->content)[1] == '#' /*&& (unsigned int)i != e->graphe->nb_rooms - 1*/)
			get_command(v, ((char *)tmp->content), 1);
	}
	return (NO_ERR);
}

void			print_rooms(VISU *v, char **room) // only for debug, delete
{
	int i;

	i = -1;
	ft_printf("list of %d rooms", v->graphe->nb_rooms);
	while ((unsigned int)++i < v->graphe->nb_rooms)
		ft_printf("%s ", room[i]);
	ft_printf("\n");
}


/*
** ### Check room info, store in list, # mark start and end
** Input: line read on stdin, broken up by space
** Returns true if room valid and successfully stored | false otherwise
*/

int				get_room(VISU *v, char **str)
{
	if (str[1] && str[2] && !str[3])
	{
		if (!is_number(str[1]) || !is_number(str[2]))
			return (ERR_COORD);
		++v->graphe->nb_rooms;
		return (NO_ERR);
	}
	return (ERR_ROOM);
}
