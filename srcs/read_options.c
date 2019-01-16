/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:50:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 19:30:08 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
** Checks if char is valid option char
** returns error code or no err
*/

static int		is_option(ENV *e, char c)
{
	(void)e;
	if (!c)
		return (1);
	if (!ft_strchr(OPTION_CHARS, c) && c)
		return (WRNG_OPTION);
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
	int				arg;
	int				i;
	static int		digit;

	arg = 0;
	while (++arg < argc)
	{
		if (argv[arg][0] != '-')
			return (ERR_ARG);
		if (!argv[arg][1] && display_warning(e, WRNG_OPTION))
			return (NO_ERR);
		i = 0;
		while (is_option(e, argv[arg][++i]) == NO_ERR)
		{
			if (ft_isdigit(argv[arg][i]))
				e->max_paths = e->max_paths * 10 * digit + argv[arg][i] - '0';
			digit = ft_isdigit(argv[arg][i]) ? 1 : 0;
			e->options |= (1 << (argv[arg][i] - 'a'));
		}
		if (argv[arg][i])
			display_warning(e, WRNG_OPTION);
	}
	display_help(e);
	return (NO_ERR);
}
