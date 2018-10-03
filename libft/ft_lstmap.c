/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:40:54 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 01:16:38 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstrrev(t_list *l, t_list *prev, t_list *next)
{
	l->next = prev;
	prev = l;
	if (next)
	{
		l = next;
		return (ft_lstrrev(l, prev, l->next));
	}
	return (l);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f) (t_list *elem))
{
	t_list	*l;
	t_list	*ll;

	if (!lst || !f)
		return (0x0);
	ll = NULL;
	while (lst)
	{
		l = ft_lstnew(lst->content, lst->content_size);
		l = f(lst);
		ft_lstadd(&ll, l);
		lst = lst->next;
	}
	if (ll && ll->next)
		return (ft_lstrrev(ll, NULL, ll->next));
	return (ll);
}
