/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_strnequ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 11:33:06 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/31 22:33:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

int		ftp_strnequ(const char *s1, const char *s2, size_t n)
{
	return (s1 && s2 ? !ftp_strncmp(s1, s2, n) : 0);
}
