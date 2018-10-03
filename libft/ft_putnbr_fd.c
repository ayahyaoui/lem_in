/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 22:10:53 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/14 22:14:00 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbrec_fd(long n, int fd)
{
	if (n / 10)
		ft_putnbrec_fd(n / 10, fd);
	ft_putchar_fd((char)(n % 10) + '0', fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	long nb;

	nb = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -1 * nb;
	}
	ft_putnbrec_fd(nb, fd);
}
