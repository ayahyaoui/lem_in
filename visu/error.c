/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 11:42:01 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 15:44:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

char 	*get_errmsg(int code)
{
	static char *msg[ERR_NB + 1] = {NULL, NOINS, ANT_INPUT, ANT_NB,
		MAXINT,
		ROOM_INPUT, ROOM_CONF, COORD, TUBE_INPUT, NOTUBE, TUBE_NOROOM, ROOM_DUP, ORDER,
		NOSTART, NOEND, LIB, MALLOC, HELP, OPTION, ARG, LENGTH};
	return (msg[code]);
}
/*
void	printlist(ENV *e, t_list *l)
{	
	t_list *tmp;

	(void)e;
	tmp = l;
	ft_printf("print list of rooms\n");
	while (tmp)
	{
		ft_printf("%s\t", (char *)(tmp->content));
		tmp = tmp->next;
	}
}
*/
int		display(VISU *v, char *str)
{
	v->fd = STDERR;
	ft_printf("{FD!}Error{EOO}", &v->fd);
	if (v->options & OPT_VERBOSE)
		ft_printf("{FD!}%s%s\n{EOO}", &v->fd, " | ", str);
	else
		ft_putchar_fd('\n', v->fd);
	return (-1);
}
