/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 13:33:38 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:05:07 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdupf(char *dest, const char *src, int to_free)
{
	int		i;
	char	*dup;
	size_t	len;
	char	*ptr;

	dup = NULL;
	ptr = (char *)(unsigned long)src;
	if (!(dup = (char *)malloc((ft_strlen(ptr) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	len = ft_strlen(ptr);
	while (len--)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	if ((to_free == 2 || to_free == 3) && src != NULL)
		ft_strdel(&ptr);
	if ((to_free == 1 || to_free == 3) && dest != NULL)
		ft_strdel(&ptr);
	return (dup);
}
