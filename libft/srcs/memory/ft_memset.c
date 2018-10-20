/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:19:30 by emuckens          #+#    #+#             */
/*   Updated: 2018/06/18 11:53:17 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*string;

	string = (unsigned char *)str;
	while (len)
	{
		*(string) = (unsigned char)c;
		--len;
		string++;
	}
	return (str);
}
