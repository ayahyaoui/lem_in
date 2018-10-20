/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 17:37:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static ENV e;

	set_env(&e);
	if ((e.err = read_instructions(&e, NULL)) && ft_printf("final err code = %d\n", e.err))
		return (display(&e, get_errmsg(e.err)));
	return (0);
}
