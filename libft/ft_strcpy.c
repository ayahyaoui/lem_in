/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:13:19 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/18 19:21:17 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *str)
{
	int i;

	i = -1;
	while (str[++i])
		dst[i] = (char)str[i];
	dst[i] = '\0';
	return (dst);
}
