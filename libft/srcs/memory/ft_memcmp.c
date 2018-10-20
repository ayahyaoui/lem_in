/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:42:54 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:20:37 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*s1_cpy;
	char	*s2_cpy;
	size_t	i;

	i = 0;
	s1_cpy = (char *)(unsigned long)s1;
	s2_cpy = (char *)(unsigned long)s2;
	while (n && s1_cpy[i] == s2_cpy[i])
	{
		i++;
		n--;
	}
	return (!n ? 0 : (unsigned char)s1_cpy[i] - (unsigned char)s2_cpy[i]);
}
