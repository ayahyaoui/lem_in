/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 22:41:20 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 03:08:10 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_printbase(int nb, size_t base)
{
	char	*str;

	str = ft_itoa_base(nb, base);
	if (str)
		write(1, str, ft_strlen(str));
}
