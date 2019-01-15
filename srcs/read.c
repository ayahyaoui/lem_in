/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:52 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/15 23:06:10 by emuckens         ###   ########.fr       */
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
//	ft_printf("type = %d endroomm = %d room = %d\n", e->type, endrooms, ROOM);
	if (nb == 1)
	{
		if ((ret = get_ants(e, words, e->type)))
		{
			display_warning(e, ret);
			return (ERR_ANT_NB);
		}
	}
	else if (e->type == ROOM && !endrooms)
	{
		if ((ret = get_room(e, words)) > 0 /*&& (ft_printf("ret = %d\n", ret)*/)
		{
			e->nb_line *= -1;
			display_warning(e, ret);
//			ft_printf("err notue = %d\n", ERR_NOTUBE);
			return (ERR_NOTUBE);
		}
	}
	else if (e->type == TUBE && ++endrooms)
	{
		if (endrooms == 1)
		{
			if ((ret = store_rooms(e)))
				display_error(e, ret);
			if ((ret = setup_room_mtrx(e, e->graphe->nb_rooms)) )
				return (ret);
		}
		if ((ret = get_tube(e, words, BOTH, 1)))
			return (endrooms == 1 ? ERR_NOTUBE : ret);//display_warning(e, ret);
	}
	else
		return (WRNG_INPUT);
//	ft_printf("start = %d end = %d\n", e->graphe->start, e->graphe->end);
	return (NO_ERR);
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
	int				gnl;

	e->nb_line = 0;
	while (!ret && (gnl = get_next_line2(STDIN, &str)) >= -1 && str)
	{
		if (e->nb_line <= 0)
			--e->nb_line;
//		ft_printf("RET = %d nbline = %d\n", ret, nbline);
		if (str[0] != '#' && ++nbline)
		{
//			ft_printf("str = %s\n", str);
			if (!(words = ft_strsplit(str, sep(str, &e->type))))
			{
				ft_strdel(&str);
				return (ERR_LIB);
			}
//			ft_printf("nbline = %d\n", nbline);
			if ((ret = dispatch_ins(e, words, nbline)) > 0 )
			{
//				ft_printf("ret dispatch = %d\n", ret);
				ft_free_strtab(&words);
				ft_strdel(&str);
				return (ret);
			}
			ft_free_strtab(&words);
		}
		else if (str[1] == '#')
		{	
			if (get_command(e, str, 0))
				++e->ins->nb_commands;
		}
		store_line_in_anthill(e, &str);
		ft_strdel(&str);
	}
	ft_strdel(&str);
	if (e->ins->nb_ants <= 0)
	{
//		ft_printf("nb ants = %d\n", e->ins->nb_ants);
		return (e->nb_line ? ERR_ANT_NB : ERR_NO_INS);
	}
	return (gnl == -1 ? ERR_LIB :  NO_ERR);
}
