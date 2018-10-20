/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endien_btl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 21:02:42 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:13:45 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_endien_btl(size_t valbe)
{
	size_t	valle;
	size_t	i;

	i = 0;
	valle = 0;
	while (i < 4)
	{
		valle |= (((valbe >> i * 8) & 0xFF) << (8 * (3 - i)));
		++i;
	}
	return (valle);
}
