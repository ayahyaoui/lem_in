/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 11:42:01 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 17:57:31 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


/*
** Retrieve string error message
** Input: error code for scanning error reference static  table
*/

char 	*get_errmsg(int code)
{
	static char *msg[ERR_NB + 1] = {NULL, NOINS, ANT_INPUT, ANT_NB,
		MAXINT,
		ROOM_INPUT, ROOM_CONF, COORD, TUBE_INPUT, NOTUBE, TUBE_NOROOM, ROOM_DUP, ORDER,
		NOSTART, NOEND, LIB, MALLOC, HELP, OPTION, ARG, NO_SOLUTION};
	return (msg[code - 1]); // verifier que -1 fonctionne toujours
}

/*
** Display error message on fd
** Input: string error message
** Differentiate regular or verbose message
** Always return -1;
*/

int		display(ENV *e, char *str)
{
	(void)e;
	e->fd = STDERR;
	ft_printf("{FD!}Error{EOO}", &e->fd);
	if (e->options & OPT_VERBOSE)
		ft_printf("{FD!}%s%s\n{EOO}", &e->fd, " | ", str);
	else
		ft_putchar_fd('\n', e->fd);
	return (-1);
}
