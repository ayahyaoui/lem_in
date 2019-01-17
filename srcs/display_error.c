/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 11:42:01 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 20:09:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Display error message and free environment
** Input: error code for scanning error reference static  table
*/

int			display_error(ENV *e, int code)
{
	static char *msg[NB_ERRORS + 1] = {NULL, NOINS, ANT_NB, NOTUBE, NOSTART,
		NOEND, SAME_START_END, LIB, MALLOC, ARG, NO_SOLUTION};

	e->fd = STDERR;
	if (e->options & OPT_COLOR)
		ft_printf("%s", COL_ERROR);
	ft_printf("{FD!}ERROR{EOO}", &e->fd);
	if (e->options & OPT_VERBOSE)
		ft_printf("{FD!}%s%s\n{EOO}", &e->fd, " | ", msg[code]);
	else
		ft_putchar_fd('\n', e->fd);
	free_env(e);
	return (1);
}

/*
** Display warning message
** Input: error code for scanning error reference static  table
*/

int			display_warning(ENV *e, int code)
{
	static char *msg[NB_WARNINGS + 1] = {NULL, ANT_INPUT, MAXINT, MININT,
		ROOM_INPUT, ROOM_CONF, ROOM_DUP, ROOM_CHAR, COORD, TUBE_NOROOM,
		TUBE_INPUT, INVALID_INPUT, HELP, OPTION, FAILED_START, FAILED_END,
		DOUBLE_START, DOUBLE_END, SAME_ROOM};

	if (code < NO_WRNG)
		return (1);
	if (!(e->options & OPT_VERBOSE))
		return (1);
	e->fd = STDERR;
	if (e->options & OPT_COLOR)
		ft_printf("%s", COL_WARNING);
	ft_printf("{FD!}WARNING{EOO}", &e->fd);
	if (e->options & OPT_VERBOSE)
		ft_printf("{FD!}%s%s\n{EOO}", &e->fd, " | ", msg[code - NB_ERRORS - 1]);
	else
		ft_putchar_fd('\n', e->fd);
	return (1);
}
