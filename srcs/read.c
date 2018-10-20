/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:52 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 17:38:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

char			sep(char *line, int *type)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(line);
	while (++i < len)
	{
		if (line[i] == '-' && (*type = TUBE))
			return ('-');
	}
	*type = ROOM;
	return (' ');
}

int				dispatch_ins(ENV *e, char **words, int nb, int endrooms)
{
	int ret;

	ret = NO_ERR;
//	ft_printf("dispatch ins, nbline = %d\n", nb);
	if (nb == 1)
		ret = get_ants(e, words, e->type);
	else if (e->type == ROOM && !endrooms)
		ret = get_room(e, words);
	else if (e->type == TUBE && (endrooms = 1))
		ret = get_tube(e, words);
	else
		return (ERR_ORDER);
	return (ret);
}

int				read_instructions(ENV *e, char *str)
{
	static int		endrooms;
	char			**words;
	int				ret;
	int				nbline;
	t_list			*line;

	ret = 0;
	nbline = 0;
	e->fd = 2;
	while (!ret && get_next_line2(STDIN, &str) > 0 && str)
	{
//		ft_printf("{FD!}while | len str = %d size str = %zu\n{EOO}", &e->fd, ft_strlen(str), sizeof(str));
		if (!(ret = get_special_line(e, str)) && ++nbline)
		{
			words = ft_strsplit(str, sep(str, &e->type));
//			ft_printf("type = %d\n", e->type);
			if (!words && (e->err = ERR_READ))
				return (INVALID_INPUT);
			if ((ret = dispatch_ins(e, words, nbline, endrooms)) && ft_printf("ret = %d\n", ret))
				return (ret);
		}
		line = ft_lstnew(ft_strdup(str), ft_strlen(str));
		ft_lstaddend(&e->anthill, line);
//		ft_printf("..continue reading...\n");
		ft_strdel(&str);
	}
//	if (e->err == NO_ERR)
		display_anthill(e->anthill);
	return (NO_ERR);
}
