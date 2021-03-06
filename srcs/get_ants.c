/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:03:30 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 19:06:59 by emuckens         ###   ########.fr       */
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
	if (str[1] || !is_number(str[0]) || type == TUBE)
		return (ERR_ANT_INPUT);
	if (ft_beyond_limiti(str[0]) == 1) 
		return (ERR_INTMAX);
	if (!(e->ins->nb_ants = ft_atoi(str[0])))
		return (ERR_ANT_NB);
	return (NO_ERR);
}
