/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:04:49 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 19:26:09 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
** Display whole anthill on termnal
*/

void		display_anthill(ENV *e)
{
	t_list *tmp;

	tmp = e->anthill;
	while (tmp && tmp->content && e->nb_line--)
	{
		ft_printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}
