/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:52 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 02:21:57 by emuckens         ###   ########.fr       */
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

	ft_printf("dispatch ins, nbline = %d\n", nb);
	if (nb == 1)
		ret = get_ants(e, words, e->type);
	else if (e->type == ROOM && !endrooms)
		ret = get_room(e, words);
	else if (e->type == TUBE && (endrooms = 1))
		ret = get_tube(e, words);
	else
		return (0);
	ft_printf("valid input\n");
	return (ret);
}

int				read_instructions(ENV *e, char *str)
{
	static int		endrooms;
	char			**words;
	int				ret;
	int				nbline;

	ret = 1;
	nbline = 0;
	while (ret && get_next_line2(STDIN, &str) > 0 && str)
	{
		ft_printf("while\n");
		if (!(ret = get_special_line(e, str)) && ++nbline)
		{
			words = ft_strsplit(str, sep(str, &e->type));
			if (!words && (e->err = ERR_READ))
				return (0);
			if (!(ret = dispatch_ins(e, words, nbline, endrooms)))
				e->err = ERR_ORDER;
		}
		ft_printf("..continue reading...\n");
	}
	return (ret);
}
