/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:19:19 by emuckens          #+#    #+#             */
/*   Updated: 2018/06/26 19:46:14 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** double cast = seule solution trouvee pour silent drop const qualifier error
*/

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_cpy;
	const char	*p;
	char		*ptr;

//	ft_putcnl('A');
	p = (const char *)(unsigned long)src;
//	ft_printf("check p: %c\n", *p);
//	ft_putcnl('B');
	ptr = (char *)(unsigned long)p;
//	ft_printf("check ptr: %c\n", *ptr);
//	ft_putcnl('C');
	dst_cpy = (char *)dst;
	while (n--)
	{
//		ft_putcnl('N');
		*dst_cpy = *ptr;
//		ft_putcnl('D');
		dst_cpy++;
//		ft_putcnl('E');
		ptr++;
//		ft_putcnl('F');
	}
	return (dst);
}
