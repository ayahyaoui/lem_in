/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:55:03 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/15 17:21:44 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
 ** ceci ne suis pas exactement le meme role que realloc
 ** elle permet de realloue lorsque que l'on connait le nombre de caractere
 ** que l'on veut garde (elle n'est pas securise on par du principe que 
 ** t est > a la taille deja alloue)
*/

void					*ft_realloc(void *previous, size_t t, size_t len_src)
{
	unsigned char *dest;

	if (previous == 0x0 || t < len_src)
		return (0x0);
	if (!(dest = (unsigned char *)malloc(sizeof(char) * t)))
		return (0x0);
	dest = ft_memcpy(dest, previous, len_src);
	ft_memdel(&previous);
	return (dest);
}
