/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftre.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 23:19:43 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/13 23:18:49 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void					*ft_realloc(void *l, size_t t, size_t len_src)
{
	unsigned char *s;

	if (!(s = (unsigned char *)malloc(sizeof(char) * t)))
		return (0x0);
	s = ft_memcpy(s, l, len_src);
	ft_memdel(l);
	return (s);
}
