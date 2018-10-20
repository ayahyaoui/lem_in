/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_nblen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:27:06 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/31 22:33:01 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

int		ftp_nblen(int n, int base)
{
	if (n < 0)
		return (n == -2147483648 ? 11 : ftp_nblen(-n, base) + 1);
	return (n / base ? ftp_nblen(n / base, base) + 1 : 1);
}
