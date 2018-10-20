/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 16:34:11 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 14:54:45 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_nbwords(char *str, int sep, int i)
{
	if (!str || str[0] == '\0')
		return (0);
	if (!str[i + 1])
		return (str[i] == sep ? 0 : 1);
	if (str[i] != sep && str[i + 1] == sep)
		return (ft_nbwords(str, sep, i + 1) + 1);
	return (ft_nbwords(str, sep, i + 1) + 0);
}
