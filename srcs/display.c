/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:04:49 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 06:10:48 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdlib.h>

/*
 ** Display whole anthill on termnal
 */

void		display_anthill(ENV *e, t_list *anthill)
{
	t_list *tmp;

	tmp = anthill;
	while (tmp && tmp->content && e->nb_line--)
	{
		ft_printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}


