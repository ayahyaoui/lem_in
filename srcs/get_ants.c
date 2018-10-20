/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:03:30 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 02:21:53 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "limits.h"

/*
** Checks ant format and stores ant number
** Input: str = line read on stdin broken up by spaces or '-',
** type = indicator of punctuation other than ' ' (i.e. TUBE)
** Returns true if ants sucessfully read and stored | false otherwise
*/

int				get_ants(ENV *e, char **str, int type)
{
	if (ft_beyond_limiti(str[0]) == 1 && (e->err = ERR_INTMAX))
		return (0);
	if (((type == TUBE) || str[1]) && (e->err = ERR_ANT_INPUT))
		return (0);
	if ((e->ins->nb_ants = ft_atoi(str[0])) <= 0)
	{
		e->err = ERR_ANT_NB;
		return (0);
	}
	ft_printf("nb ants: %d\n", e->ins->nb_ants);
	return (1);
}
