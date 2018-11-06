/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:50:41 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/04 19:55:30 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

/*
** Malloc square int **tab
** Input: size = nb of tab rows (= nb of tab columns)
** Returns true for successful allocation | False otherwise
*/

static int		setup_room_mtrx(ENV *e, int size)
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

static int		get_room_index(ENV *e, char *str)
{
	int i;

	i = -1;
	while ((unsigned int)++i < e->graphe->nb_rooms)
		if (ft_strequ(e->ins->room[i], str))
			return (i);
	return (-1);
}

/*
** 
*/

static void		handle_way_spec(ENV *e, char **str1, char **str2, int *way)
{
	if (e->options & OPT_WAY)
	{
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
			ft_printf("after handle zqy spec, str0 = %s str1 = %s way = %d\n", *str1, *str2, *way);
	}
}

/*
** Read tube information, setup and fill adjacency matrix, check start and end
** existence
** Input: line read on stdin, broken up at '-'
** Returns true if tube info successfully read and stored in matrix | false
** otherwise
*/

int				get_tube(ENV *e, char **str, int way)
{
	static int	it;
	char		**check;
	int			i;
	int			j;

	if (!it && ++it && setup_room_mtrx(e, e->graphe->nb_rooms))
		return (ERR_ALLOC);
	if (it == 1 && ++it)
		store_rooms(e);
	if (!str[1] || (check = ft_strsplit(str[1], ' '))[1]) // si rajout de longueur de tube, c'est ici
	{
		free_strtab(&check);
		return (ERR_TUBE);
	}
	free_strtab(&check);
	handle_way_spec(e, &str[0], &str[1], &way);
			ft_printf("after handle zqy spec, str0 = %s str1 = %s way = %d\n", str[0], str[1], way);
	
	i = get_room_index(e, str[0]);
	j = get_room_index(e, str[1]);
	if ((i == -1 || j == -1))
		return (ERR_NOROOM);
	if ((way == FORWARD || way == BOTH) && (e->graphe->map[i][j] = 1))
		--str[1];
	if (way == BACKWARD || way == BOTH)
		e->graphe->map[j][i] = 1;
	++e->graphe->nb_tubes;
	return (NO_ERR);
}
