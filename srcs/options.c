/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:50:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/07 15:49:40 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			is_option(char c)
{
	if (!ft_strchr("clvw", c) || !c)
		return (ERR_OPTION);
	return (NO_ERR);
}

/*
** Read arguments starting with -, modify binary tracker
** Input: argv, argc
** Returns -1 if option error, otherwise index of first non option arg.
** Options value is stored in env
*/

int				read_options(ENV *e, char **argv, int argc)
{
	int arg;
	int i;

	arg = 1;
	while (arg < argc)
	{
		if (argv[arg][0] != '-')
			return (ERR_ARG);
		i = 1;
		if (!argv[arg][1])
			return (ERR_OPTION);
		while (!is_option(argv[arg][i]))
		{
			e->options |= (1 << (argv[arg][i] - 'a'));
			++i;
		}
		if (argv[arg][i])
			return (ERR_OPTION);
		++arg;
	}
	return (NO_ERR);
}
