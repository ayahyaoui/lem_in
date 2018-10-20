/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:51:02 by emuckens          #+#    #+#             */
/*   Updated: 2018/01/09 14:58:27 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(char *s1, char *s2, int to_free)
{
	char *str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	if ((to_free == 1 || to_free == 3) && s1)
		ft_strdel((char **)&s1);
	if ((to_free == 2 || to_free == 3) && s2)
		ft_strdel((char **)&s2);
	return (str);
}
