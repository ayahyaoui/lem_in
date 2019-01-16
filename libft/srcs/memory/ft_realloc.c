/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:22:37 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 20:56:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** NB: ne suit pas exactement le meme role que realloc:
** permet de realloueer lorsque que l'on connait le nombre de caracteres
** que l'on veut garde
** Elle n'est pas securise, s'assurer en amont que t > a la taille deja allouee)
*/

void		*ft_realloc(void *previous, size_t t, size_t len_src)
{
	unsigned char *dest;

	if (!previous  || t < len_src)
		return (0x0);
	if (!(dest = (unsigned char *)ft_memalloc(sizeof(unsigned char) * t)))
		return (0x0);
	dest = ft_memcpy(dest, previous, len_src);
	ft_memdel(&previous);
	return (dest);
}
