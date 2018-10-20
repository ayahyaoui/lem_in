/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:02:30 by emuckens          #+#    #+#             */
/*   Updated: 2017/11/22 19:40:43 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_beg;
	t_list *new_el;

	if (!lst)
		return (NULL);
	new_el = ft_lstnew(f(lst)->content, f(lst)->content_size);
	if (!new_el)
		return (NULL);
	new_beg = new_el;
	lst = lst->next;
	while (lst)
	{
		new_el->next = ft_lstnew(f(lst)->content, f(lst)->content_size);
		if (new_el->next == NULL)
			return (NULL);
		lst = lst->next;
		new_el = new_el->next;
	}
	new_el->next = NULL;
	return (new_beg);
}
