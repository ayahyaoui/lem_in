/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 23:34:37 by anyahyao          #+#    #+#             */
/*   Updated: 2018/08/06 07:17:52 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_str2len(char **str)
{
	int		res;
	int		i;

	i = -1;
	res = 0;
	while (str[++i] != 0x0)
		res += ft_strlen(str[i]);
	return (res);
}

char		*ft_strmerge(char **str)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	i = -1;
	if (!str || !*str)
		return (0x0);
	len = ft_str2len(str);
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (0x0);
	i = -1;
	len = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			res[len] = str[i][j];
			len++;
		}
	}
	res[len] = '\0';
	return (res);
}
