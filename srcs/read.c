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

int				dispatch_ins(ENV *e, char **words, int nb)
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

int				read_instructions(ENV *e, char *str, int nbline, int ret)
{
	char			**words;
	char			*tmp;
	t_list			*line;

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
				free_strtab(&words);
				ft_strdel(&str);
				return (ret);
			}
			free_strtab(&words);
		}
		else if (str[1] == '#' /*&& ft_printf("check str: %s\n", str) */&&
get_command(e, str, 0))
		{
			++e->ins->nb_commands;
					}
		line = ft_lstnew(tmp = ft_strdup(str), ft_strlen(str) + 1);
		ft_strdel(&tmp); //ajoute pour pouvoir free le contenu duplique
		ft_lstaddend(&e->anthill, line);
		ft_strdel(&str);
	}
	ft_strdel(&str);
	return (NO_ERR);
}
