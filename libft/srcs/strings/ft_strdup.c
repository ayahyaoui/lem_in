/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 13:33:38 by emuckens          #+#    #+#             */
/*   Updated: 2018/06/26 16:15:32 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;
	char	*ptr;
	size_t	len;

	ptr = (char *)(unsigned long)src;
	if (!(dup = (char *)malloc(ft_strlen(ptr + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	len = ft_strlen(ptr);
	while (len--)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
