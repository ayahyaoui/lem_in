/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:50:41 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/21 01:40:56 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Malloc square int **tab
** Input: size = nb of tab rows (= nb of tab columns)
** Returns true for successful allocation | False otherwise
*/

static int		setup_room_mtrx(ENV *e, int size)
{
	int		i;

	i = 0;
	if (!(e->graphe->map = (int **)ft_memalloc(sizeof(int *) * size)))
		return (ERR_ALLOC);
	while (i < size)
	{
		if (!(e->graphe->map[i] = (int *)ft_memalloc(sizeof(int) * size)))
			return (ERR_ALLOC);
		++i;
	}
	return (NO_ERR);
}

/*
** Determine index (i.e. place in list) of a given room
** Input: room list, room name
** Returns index of room if found | -1 otherwise
*/

static int		get_room_index(t_list *l, char *str)
{
	int i;

	i = -1;
	while (l && ++i >= 0 && !ft_strequ(str, ((t_room *)(l->content))->name))
		l = l->next;
	ft_printf("room exists in %d\n", i);
	return (i);
}

/*
** Read tube information, setup and fill adjacency matrix, check start and end
** existence
** Input: line read on stdin, broken up at '-'
** Returns true if tube info successfully read and stored in matrix | false
** otherwise
*/

int				get_tube(ENV *e, char **str, int endrooms)
{
	static int	it;
	char		**check;
	int			i;
	int			j;
	
	(void)endrooms;
//	if (str[1] && !is_number(str[1]) && endrooms == 1)
//		return (ERR_ROOM_CONF);
	if (!it && ++it && setup_room_mtrx(e, ft_lstsize(e->ins->rooms)))
		return (ERR_ALLOC);
	if (!str[1] || (check = ft_strsplit(str[1], ' '))[1]) // si rajout de longueur de tube, c'est ici
		return (ERR_TUBE);
	i = get_room_index(e->ins->rooms, str[0]);
	j = get_room_index(e->ins->rooms, str[1]);
	if ((i == -1 || j == -1))
		return (ERR_NOROOM);
	e->graphe->map[i][j] = 1;
	e->graphe->map[j][i] = 1;
	++e->graphe->nb_tubes;
	return (NO_ERR);
}
