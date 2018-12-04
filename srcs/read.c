/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:52 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/07 16:03:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"
#include <stdlib.h>

/*
** Determine if string should be parsed by '-' (tubes) or ' ' (rooms)
** Set pointer on type accordingly
** Return separating character for use in strsplit
*/

char			sep(char *line, int *type)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(line);
	while (++i < len)
		if (line[i] == '-' && (*type = TUBE))
			return ('-');
	*type = ROOM;
	return (' ');
}

/*
** Parse input and store significant information as ants, room or tube
** Considers first tube as sign that all rooms are known, set up adjacency matrix
** to store tube information relative to rooms
** Return error code in case of error, no err otherwise
*/

static int			dispatch_ins(ENV *e, char **words, int nb)
{
	int ret;
	static int		endrooms;

	ret = NO_ERR;
	if (nb == 1)
	{
		ret = get_ants(e, words, e->type);
		return (ret);
	}
	else if (e->type == ROOM && !endrooms)
		ret = get_room(e, words);
	else if (e->type == TUBE && ++endrooms)
	{
		if (endrooms == 1)
		{
			ret = store_rooms(e);
			if (ret || (ret = setup_room_mtrx(e, e->graphe->nb_rooms)))
				return (ret);
		}
		ret = get_tube(e, words, BOTH, 1);
	}
	else
		return (ERR_ORDER);
	return (ret);
}

/*
** Store line in anthill linked list, for display at the end of the program
** Input: string line 
*/

void				store_line_in_anthill(ENV *e, char **str)
{
	t_list *line;
	char	*tmp;

	line = ft_lstnew(tmp = ft_strdup(*str), ft_strlen(*str) + 1);
	ft_strdel(&tmp);
	ft_lstaddend(&e->anthill, line);
}

/*
** Read input one line at a time, split all non comment and command instruction
** and send to type detection
** Store line as string in anthill linked list
** Return error code in case of error, no err otherwise
*/

int				read_instructions(ENV *e, char *str, int nbline, int ret)
{
	char			**words;

	while (!ret && get_next_line2(STDIN, &str) > 0 && str)
	{
		if (str[0] != '#' && ++nbline)
		{
			if (!(words = ft_strsplit(str, sep(str, &e->type))))
			{
				ft_strdel(&str);
				return (ERR_READ);
			}
			if ((ret = dispatch_ins(e, words, nbline)))
			{
				ft_free_strtab(&words);
				ft_strdel(&str);
				return (ret);
			}
			ft_free_strtab(&words);
		}
		else if (str[1] == '#' && get_command(e, str, 0))
			++e->ins->nb_commands;
		store_line_in_anthill(e, &str);
		ft_strdel(&str);
	}
	ft_strdel(&str);
	return (NO_ERR);
}
