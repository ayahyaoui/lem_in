/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:48:19 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 04:01:34 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t s)
{
	size_t	i;
	char	*str;

	if (!(str = (char *)malloc((s + 1) * sizeof(char))))
		return (0x0);
	i = -1;
	while (++i < s + 1)
		str[i] = '\0';
	return (str);
}
