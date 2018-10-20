/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_strequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 11:24:28 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/31 22:31:48 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

int		ftp_strequ(const char *s1, const char *s2)
{
	return (s1 && s2 ? !ftp_strcmp(s1, s2) : 0);
}
