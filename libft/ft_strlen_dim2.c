/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_dim2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 05:43:09 by anyahyao          #+#    #+#             */
/*   Updated: 2018/08/01 05:45:40 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	on cherche a calulcler la taille de la deuxieme dimension
**	on par du principe que la derniere case est suivi d'un NULL
*/

size_t	ft_strlen_dim2(char **str)
{
	size_t i;

	i = 0;
	while (str[i] != 0x0)
		i++;
	return (i);
}
