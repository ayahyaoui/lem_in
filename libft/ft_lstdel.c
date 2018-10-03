/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 22:46:43 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/18 20:18:38 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void *, size_t))
{
	t_list	*l;
	t_list	*ll;

	l = *alst;
	while (l)
	{
		if (l->next != 0x0)
		{
			ll = l->next;
			ft_lstdelone(&l, del);
			free(l);
			l = ll;
		}
		ft_lstdelone(&l, del);
		free(l);
	}
	*alst = 0x0;
}
