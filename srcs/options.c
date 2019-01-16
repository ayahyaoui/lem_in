/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:50:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 07:33:48 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Checks if char is valid option char
** returns error code or no err
*/

static int			is_option(char c)
{
	if (!ft_strchr(OPTION_CHARS, c) || !c)
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
	int arg;
	int i;
	static int		digit;

	arg = 1;
	while (arg < argc)
	{
		if (argv[arg][0] != '-')
			return (ERR_ARG);
		i = 1;
		if (!argv[arg][1] && display_warning(e, WRNG_OPTION))
			return (WRNG_OPTION);
		while (is_option(argv[arg][i]) == NO_ERR)
		{
			if (ft_isdigit(argv[arg][i]))
			{
				e->max_paths = e->max_paths * 10 * digit + argv[arg][i] - '0';
				digit = 1;
			}
			else
				digit = 0;
			e->options |= (1 << (argv[arg][i] - 'a'));
			++i;
		}

		if (argv[arg][i] && display_warning(e, WRNG_OPTION))
			return (WRNG_OPTION);
		++arg;
	}
	if (e->options & OPT_HELP)
	{
		ft_printf("------------------------------------------------------\n\n");	
		if (!(e->options & OPT_COLOR))
			display_help(e, COLB_OFF, COLF_OFF);
		else
			display_help(e, COL_HELP, COL_TYPES);
		ft_printf("------------------------------------------------------\n\n");	
	}
	return (NO_ERR);
}
