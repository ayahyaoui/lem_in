/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:13:07 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/11 21:15:05 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *sr1, const char *sr2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)sr1;
	str2 = (unsigned char*)sr2;
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return ((int)str1[i] - (int)str2[i]);
}
