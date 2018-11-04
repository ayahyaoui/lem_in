/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:52 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/21 01:41:15 by emuckens         ###   ########.fr       */
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
		ret = get_ants(e, words, e->type);
	else if (e->type == ROOM && !endrooms)
		ret = get_room(e, words);
	else if (e->type == TUBE && ++endrooms)
		ret = get_tube(e, words, endrooms);
	else
		return (ERR_ORDER);
	return (ret);
}

int				read_instructions(ENV *e, char *str, int nbline, int ret)
{
	char			**words;
	t_list			*line;

	while (!ret && get_next_line2(STDIN, &str) > 0 && str)
	{
		if ((str[0] != '#' || !(get_command(e, str))) && ++nbline)
		{
			if (!(words = ft_strsplit(str, sep(str, &e->type))))
				return (ERR_READ);
			if ((ret = dispatch_ins(e, words, nbline)))
			{
				free_strtab(&words);
				ft_strdel(&str);
				return (ret);
			}
			else
				free_strtab(&words);
		}
		line = ft_lstnew(str, ft_strlen(str));
		ft_lstaddend(&e->anthill, line);
		ft_strdel(&str);
	}
	apply_commands(e);
	display_anthill(e->anthill);
	return (NO_ERR);
}
