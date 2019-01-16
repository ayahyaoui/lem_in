/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tubes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:50:41 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/17 00:44:15 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
** Malloc square int **tab
** Input: size = nb of tab rows (= nb of tab columns)
** Returns true for successful allocation | False otherwise
*/

int					setup_room_mtrx(ENV *e, int size)
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

static int			get_room_index(ENV *e, char *str)
{
	int i;

	i = -1;
	while ((unsigned int)++i < e->graphe->nb_rooms)
		if (ft_strnequ(e->ins->room[i].name, str,
				ft_strlen(e->ins->room[i].name)))
			return (i);
	return (-1);
}
/*
** Read tube information, setup and fill adjacency matrix, check start and end
** existence
** Input: line read on stdin, broken up at '-'
** Returns true if tube info successfully read and stored in matrix | false
** otherwise
*/

int					get_tube(ENV *e, char **str, int way, int len)
{
	char		**check;
	int			i;
	int			j;

	(void)way;
	if (!str[1] || str[2])
	{
		ft_free_strtab(&check);
		display_warning(e, WRNG_TUBE);
		return (ERR_NOTUBE);
	}
	i = get_room_index(e, str[0]);
	j = get_room_index(e, str[1]);
	if ((i == -1 || j == -1))
		return (display_warning(e, WRNG_TUBE_NOROOM));
	if (i == j)
		display_warning(e, WRNG_SAME_ROOM);
	e->graphe->map[i][j] = len;
	e->graphe->map[j][i] = len;
	++e->graphe->nb_tubes;
	return (NO_ERR);
}
