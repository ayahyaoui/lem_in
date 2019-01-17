/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:52 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/17 01:11:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Determine if string should be parsed by '-' (tubes) or ' ' (rooms)
** Set pointer on type accordingly
** Return separating character for use in strsplit
*/

static char			sep(char *line, int *type)
{
	int		i;
	int		len;
	char	**split;

	i = -1;
	len = ft_strlen(line);
	while (++i < len)
	{
		if (!(split = ft_strsplit(line, ' ')))
			return (0);
		if (line[i] == '-' && !split[1] && (*type = TUBE))
		{
			ft_free_strtab(&split);
			return ('-');
		}
		ft_free_strtab(&split);
	}
	*type = ROOM;
	return (' ');
}

/*
** Parse input and store significant information as ants, room or tube
** Detects first tube as sign that all rooms are known, set up adjacency matrix
** to store tube information relative to rooms
** Input: split words from input line, int nb of significant line from begining
** of the anthill
** Return error code in case of error, no err otherwise
*/

static int			dispatch_ins(ENV *e, char **words, int nb)
{
	int				ret;
	static int		endroom;

	if (!(ret = NO_ERR) && nb == 1)
	{
		if ((ret = get_ants(e, words, e->type)))
			return (ERR_ANT_NB);
	}
	else if (e->type == ROOM && !endroom)
	{
		if ((ret = get_room(e, words)))
			return (ERR_NOTUBE);
	}
	else if (e->type == TUBE && ++endroom)
	{
		if (endroom == 1 && (ret = store_rooms(e)))
			return (ret);
		if (endroom == 1 && (ret = setup_room_mtrx(e, e->graphe->nb_rooms)))
			return (ret);
		if ((ret = get_tube(e, words, BOTH, 1)) < NO_WRNG && ret)
			return (endroom == 1 ? ERR_NOTUBE : ret);
	}
	else
		display_warning(e, WRNG_INPUT);
	return (NO_ERR);
}

/*
** Store line in anthill linked list, for display at the end of the program
** Input: string line
*/

void				store_line_in_anthill(ENV *e, char *str)
{
	t_list	*line;

	line = ft_lstnew(str, ft_strlen(str) + 1);
	ft_lstaddend(&e->anthill, line);
}

/*
** detect significant line (not comment or command), get and prepare for parser
** Input: current string  line from input, pointer on line number in anthill
** to adapt display in certain cases
** Return: error code or no error
*/

int					parse_significant_line(ENV *e, char **str, int *nbline)
{
	char		**words;
	int			ret;

	if ((*str)[0] != '#' && ++(*nbline))
	{
		if (!(words = ft_strsplit(*str, sep(*str, &e->type))))
		{
			ft_strdel(str);
			return (ERR_LIB);
		}
		if ((ret = dispatch_ins(e, words, *nbline)))
		{
			ft_free_strtab(&words);
			ft_strdel(str);
			return (ret);
		}
		ft_free_strtab(&words);
	}
	return (NO_ERR);
}

/*
** Read input one line at a time, detect type and send to appropriate parser
** Store line as string in anthill linked list
** Input: current string line from input, line number in anthill to adapt
** in certain cases
** Return error code in case of error, no err otherwise
*/

int					read_instructions(ENV *e, char *str)
{
	int				gnl;
	int				ret;
	int				nbline;

	ret = 0;
	nbline = 0;
	while (!ret && (gnl = get_next_line2(STDIN, &str)) >= -1 && str)
	{
		e->nb_line -= e->nb_line <= 0 ? 1 : 0;
		if ((ret = parse_significant_line(e, &str, &nbline)) == NO_ERR)
		{
			get_command(e, str, 0);
			store_line_in_anthill(e, str);
		}
		ft_strdel(&str);
	}
	ft_strdel(&str);
	if (e->ins->nb_ants <= 0)
		return (e->nb_line ? ERR_ANT_NB : ERR_NO_INS);
	return (gnl == -1 ? ERR_LIB : NO_ERR);
}
