/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 11:24:28 by emuckens          #+#    #+#             */
/*   Updated: 2018/09/30 20:12:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(const char *s1, const char *s2)
{
//	ft_printf("in strequ s1 = %s s2 = %s\n", s1, s2);
	return (s1 && s2 ? !ft_strcmp(s1, s2) : 0);
}
