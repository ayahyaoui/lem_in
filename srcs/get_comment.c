/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:01:15 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/20 02:13:02 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "libft.h"

/*
** ### Add comment or command to list
** Input: type (# or ##), string for end display
** content_size set to UNDEALT, to detect all unapplied special actions upon
** reaching next significant line (room or link)
*/

static void		add_special(ENV *e, int type, char *str)
{
	t_special 	*details;
	t_list		*new;

	if (!(details = (t_special *)ft_memalloc(sizeof(details))))
	{
		e->err = ERR_ALLOC;
		return ;
	}
	details->str = ft_strdup(str);
	details->type = type;
	new = ft_lstnew(details, UNDEALT);
	ft_lstadd(&e->ins->special, new);
}

/*
** ### Check comment format, marks start and end for following room reading
** Input: line read on stdin, not broken up
** Prints comment and returns true if comment OK | false otherwise
*/

int				get_special_line(ENV *e, char *str)
{
	if (str[0] != '#')
		return (0);
	if (str[1] && str[1] != '#')
	{
		add_special(e, COMMENT, str);
		return (1);
	}
	add_special(e, COMMAND, str);
//	if (ft_strequ(str, "##start") && e->graphe->start != -2)
//		e->graphe->start = -2;
//	else if (ft_strequ(str, "##end") && e->graphe->start != -2)
//		e->graphe->end = -2;
//	ft_printf("%s\n", str);
	return (1);
}
