/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:03:30 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 19:34:08 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Checks ant format and stores ant number
** Input: str = line read on stdin broken up by spaces or '-',
** type = indicator of punctuation other than ' ' (i.e. TUBE)
** Returns true if ants sucessfully read and stored | false otherwise
*/

int				get_ants(ENV *e, char **str, int type)
{
	if (str[1] || !ft_isnumber(str[0]) || type == TUBE || str[0][0] == '-')
	{
		e->ins->nb_ants = 0;
		display_warning(e, WRNG_ANT_INPUT);
		return (ERR_ANT_NB);
	}
	if (ft_beyond_limiti(str[0]) == 1)
	{
		display_warning(e, WRNG_INTMAX);
		return (ERR_ANT_NB);
	}
	if (!(e->ins->nb_ants = ft_atoi(str[0])))
		return (ERR_ANT_NB);
	return (NO_ERR);
}
