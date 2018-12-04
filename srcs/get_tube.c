/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:50:41 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/07 16:44:45 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

/*
** Malloc square int **tab
** Input: size = nb of tab rows (= nb of tab columns)
** Returns true for successful allocation | False otherwise
*/

int		setup_room_mtrx(ENV *e, int size)
{
	int		i;

	i = -1;
	if (!(e->graphe->map = (char **)ft_memalloc(sizeof(char *) * size)))
		return (ERR_ALLOC);
	while (++i < size)
		if (!(e->graphe->map[i] = (char *)ft_memalloc(sizeof(char) * size)))
			return (ERR_ALLOC);
	return (NO_ERR);
}

/*
** Determine index (i.e. place in list) of a given room
** Input: room list, room name
** Returns index of room if found | -1 otherwise
*/

static int		get_room_index(ENV *e, char *str, int n)
{
	int i;

	i = -1;
	while ((unsigned int)++i < e->graphe->nb_rooms)
	{
		if (!n && ft_strequ(e->ins->room[i].name, str))
			return (i);
		else if (n && ft_strnequ(e->ins->room[i].name, str, n))
			return (i);
	}
	return (-1);
}

/*
** Handle optional possibility to use ->, <- or <-> (= -) to indicate flow direction
** in tube
** Input: 2 strings for room names, pointer on way marker to set to FORWARD,
** BACKWARD or BOTH 
*/

static void		handle_way_spec(ENV *e, char **str1, char **str2, int *way)
{
	if (!(e->options & OPT_WAY))
		return;
	if ((*str2)[0] == '>')
	{
		*way = FORWARD;
		++(*str2);
	}
	if ((*str1)[ft_strlen(*str1) - 1] == '<')
	{
		*way = (*way == FORWARD ? BOTH : BACKWARD);
		(*str1)[ft_strlen(*str1) - 1] = 0;
	}
}

/*
** Read tube information, setup and fill adjacency matrix, check start and end
** existence
** Input: line read on stdin, broken up at '-'
** Returns true if tube info successfully read and stored in matrix | false
** otherwise
*/

int				get_tube(ENV *e, char **str, int way, int len)
{
	char		**check;
	int			i;
	int			j;

	if (!str[1] || str[2]
		|| ((check = ft_strsplit(str[1], ' '))[1] && !(e->options & OPT_LENGTH)))
	{
		ft_free_strtab(&check);
		return (ERR_TUBE);
	}
	handle_way_spec(e, &str[0], &str[1], &way);
	i = get_room_index(e, str[0], 0);
	j = get_room_index(e, str[1], len > 1 ? ft_strlen(check[0]) : 0);
	ft_free_strtab(&check);
	if ((i == -1 || j == -1))
		return (ERR_NOROOM);
	if ((way == FORWARD || way == BOTH) && (e->graphe->map[i][j] = len))
		str[1] -= (e->options & OPT_WAY) ? 1 : 0;
	if (way == BACKWARD || way == BOTH)
		e->graphe->map[j][i] = len;
	++e->graphe->nb_tubes;
	return (NO_ERR);
}
