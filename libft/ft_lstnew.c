/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:40:54 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 04:05:52 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t size)
{
	t_list	*l;

	if (!(l = (t_list *)malloc(sizeof(t_list))))
		return (0x0);
	if (!content)
	{
		l->content = 0x0;
		l->content_size = 0;
	}
	else
	{
		if (!(l->content = (void*)malloc(sizeof((*l->content)) * size)))
			return (0x0);
		l->content = ft_memcpy(l->content, content, size);
		l->content_size = size;
	}
	l->next = (0x0);
	return (l);
}
