/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:19:52 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 18:20:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns list elements at index indicated in parameters
*/

t_list		*ft_lstel(t_list *l, int index)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = l;
	while (i < index)
	{
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}
