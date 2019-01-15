/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:50:41 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/15 23:09:10 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdlib.h>

/*
** Malloc square int **tab
** Input: size = nb of tab rows (= nb of tab columns)
** Returns true for successful allocation | False otherwise
*/

int		setup_room_mtrx(VISU *v, int size)
{
	int		i;

	i = -1;
	if (!(v->graphe->map = (char **)ft_memalloc(sizeof(char *) * size)))
		return (ERR_ALLOC);
	while (++i < size)
		if (!(v->graphe->map[i] = (char *)ft_memalloc(sizeof(char) * size)))
			return (ERR_ALLOC);
	return (NO_ERR);
}

/*
** Determine index (i.e. place in list) of a given room
** Input: room list, room name
** Returns index of room if found | -1 otherwise
*/

int		get_room_index(VISU *v, char *str, int n)
{
	int i;

	i = -1;
	while ((unsigned int)++i < v->graphe->nb_rooms)
	{
		if (!n && ft_strequ(v->ins->room[i].name, str))
			return (i);
		else if (n && ft_strnequ(v->ins->room[i].name, str, n))
			return (i);
	}
	return (-1);
}

/*
** 
*/

static void		handle_way_spec(VISU *v, char **str1, char **str2, int *way)
{
	if (!(v->options & OPT_WAY))
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

int				get_tube(VISU *v, char **str, int way, int len)
{
	char		**check = NULL;
	int			i;
	int			j;
(void)len;
	handle_way_spec(v, &str[0], &str[1], &way);
	i = get_room_index(v, str[0], 0);
	j = get_room_index(v, str[1], 0);
	free_strtab(&check);
	if ((way == FORWARD || way == BOTH) && (v->graphe->map[i][j] = 1))
		str[1] -= (v->options & OPT_WAY) ? 1 : 0;
	if (way == BACKWARD || way == BOTH)
		v->graphe->map[j][i] = 1;
	++v->graphe->nb_tubes;
	return (NO_ERR);
}
