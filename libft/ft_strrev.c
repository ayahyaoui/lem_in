/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 22:00:18 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/19 22:33:06 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp[1024];

	if (!str || (i = ft_strlen(str)) > 1024)
		return (-1);
	j = i - 1;
	while (--i > -1)
		tmp[i] = str[j - i];
	i = -1;
	while (++i < j + 1)
		str[i] = tmp[i];
	str[i] = '\0';
	return (1);
}
