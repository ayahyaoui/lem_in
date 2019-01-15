/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 11:42:01 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 22:11:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_failing_error(int err)
{
	return (err == ERR_START || err == ERR_NO_INS || err == ERR_NOROOM
		|| err == ERR_ORDER ||  err == ERR_ANT_NB || err == ERR_ANT_INPUT
		|| err == ERR_LIB || err == ERR_ALLOC || err == ERR_START
		|| err == ERR_SAME || err == ERR_END  || err == ERR_ARG
		|| err == ERR_NOTUBE);
}


/*
** Retrieve string error message
** Input: error code for scanning error reference static  table
*/

int	display_error(ENV *e, int code)
{
	static char *msg[NB_ERRORS + 1] = {NULL, NOINS, ANT_INPUT, ANT_NB, NOTUBE,
		ORDER, NOSTART, NOEND, SAME_START_END, LIB, MALLOC, ARG, NO_SOLUTION};

	e->fd = STDERR;
	if (e->options & OPT_COLOR)
		ft_printf("%s", COL_ERROR);
	ft_printf("{FD!}Error{EOO}", &e->fd);
	if (e->options & OPT_VERBOSE)
		ft_printf("{FD!}%s%s\n{EOO}", &e->fd, " | ", msg[code]);
	else
		ft_putchar_fd('\n', e->fd);
		
	free_env(e);
	return (1);
}

int	display_warning(ENV *e, int code)
{
	static char *msg[NB_WARNINGS + 1] = {NULL, ANT_COMMAND, MAXINT,
		ROOM_INPUT, ROOM_CONF, ROOM_DUP, ROOM_CHAR, COORD,
		TUBE_NOROOM, TUBE_INPUT, HELP, OPTION, FAILED_START, FAILED_END,
		DOUBLE_START, DOUBLE_END};

	e->fd = STDERR;
	if (e->options & OPT_COLOR)
		ft_printf("%s", COL_WARNING);
	ft_printf("{FD!}Warning{EOO}", &e->fd);
	if (e->options & OPT_VERBOSE)
		ft_printf("{FD!}%s%s\n{EOO}", &e->fd, " | ", msg[code]);
	else
		ft_putchar_fd('\n', e->fd);
	if (!(code >= WRNG_FAILED_START && code <= WRNG_DOUBLE_END))
		display_anthill(e->anthill);
	return (1);
}


/*
** Display error message on fd
** Input: string error message
** Differentiate regular or verbose message
** Must always handle freeing allocated memory
** Always return -1;
*/

