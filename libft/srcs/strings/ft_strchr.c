/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:12:02 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:35:23 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *ptr;

	ptr = (char *)(unsigned long)s;
	if (!s)
		return (NULL);
	if (!c)
		return (ptr + ft_strlen(ptr));
	while (*s)
	{
		if (*s == c)
			return (ptr);
		s++;
	}
	return (0);
}
