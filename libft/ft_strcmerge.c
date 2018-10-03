/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmerge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 06:44:49 by anyahyao          #+#    #+#             */
/*   Updated: 2018/08/06 06:45:56 by anyahyao         ###   ########.fr       */
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
		res += ft_strlen(str[i]) + 1;
	return (res);
}

char		*ft_strcmerge(char **str, char c)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	i = -1;
	if (!str || !*str)
		return (0x0);
	len = ft_str2len(str);
	if (!(res = (char *)malloc(sizeof(char) * len)))
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
		res[len++] = c;
	}
	res[len - 1] = '\0';
	return (res);
}
