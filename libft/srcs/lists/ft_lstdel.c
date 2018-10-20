/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 19:03:03 by emuckens          #+#    #+#             */
/*   Updated: 2017/11/22 19:39:32 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *new_beg;

	if ((*alst)->next != NULL)
	{
		new_beg = (*alst)->next;
		ft_lstdelone(alst, del);
		ft_lstdel(&new_beg, del);
	}
	else
		ft_lstdelone(alst, del);
	*alst = NULL;
}
