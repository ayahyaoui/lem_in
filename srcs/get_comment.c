/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:01:15 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 22:59:18 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

/*
** ### Check comment format, marks start and end for following room reading
** Input: line read on stdin, not broken up
** Prints comment and returns true if comment OK | false otherwise
*/

int				get_special_line(ENV *e, char *str)
{
	t_special	*details;
	t_list		*new;

	if (str[0] != '#')
		return (0);
	if (str[1] != '#')
		return (1);
	if (!(details = (t_special *)ft_memalloc(sizeof(details))))
		return (ERR_ALLOC);
	details->str = ft_strdup(str);
	details->status = UNDEALT;
	new = ft_lstnew(details, sizeof(*details));
	ft_lstadd(&e->ins->special, new);
//	ft_printf("check new special = %s\n",
//			((t_special *)(e->ins->special->content))->str);
	return (1);
}
