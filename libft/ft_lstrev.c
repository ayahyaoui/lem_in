/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 19:07:17 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 01:12:27 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstrev_rec(t_list *l, t_list *prev, t_list *next)
{
	l->next = prev;
	prev = l;
	if (next)
	{
		l = next;
		return (ft_lstrev_rec(l, prev, l->next));
	}
	return (l);
}

t_list			*ft_lstrev(t_list *l)
{
	if (!l)
		return (0x0);
	if (l->next)
		return (ft_lstrev_rec(l, NULL, l->next));
	return (l);
}
