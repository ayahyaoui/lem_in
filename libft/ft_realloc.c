/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftre.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 23:19:43 by anyahyao          #+#    #+#             */
/*   Updated: 2017/12/17 00:42:33 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_realloc(char *l, int t)
{
	char	*s;

	if (!(s = (char *)malloc(sizeof(char) * t)))
		return (0x0);
	s = ft_strcpy(s, l);
	free(l);
	return (s);
}
