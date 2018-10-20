/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 14:50:54 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:57:20 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnewf(void const *content, size_t content_size)
{
	t_list *new_el;

	if (!(new_el = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new_el->content = NULL;
		new_el->content_size = 0;
	}
	else
	{
		if (!(new_el->content = ft_memalloc(content_size)))
		{
			free(new_el);
			return (NULL);
		}
		new_el->content = ft_memmove(new_el->content, content, content_size);
		new_el->content_size = content_size;
	}
	new_el->next = NULL;
	free((void *)(unsigned long)content);
	return (new_el);
}
