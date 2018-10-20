/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:01:04 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:36:21 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*ptr;

	ptr = (char *)(unsigned long)s;
	len = ft_strlen(ptr);
	while (*(s + len) != c && len)
		len--;
	return (*(s + len) == c ? ptr + len : 0);
}
