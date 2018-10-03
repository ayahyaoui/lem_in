/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:13:15 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/18 18:39:30 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *l, void (*f) (t_list *elem))
{
	t_list	*ll;

	if (l && f)
	{
		ll = l;
		while (ll)
		{
			f(ll);
			ll = ll->next;
		}
	}
}
