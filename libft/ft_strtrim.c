/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:43:39 by anyahyao          #+#    #+#             */
/*   Updated: 2017/11/20 03:58:44 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*res;
	int		t;

	t = 0;
	i = 0;
	if (!s)
		return (0x0);
	j = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (j > i && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	if (!(res = (char *)malloc(sizeof(char) * j - i + 2)))
		return (0x0);
	while (i <= j)
	{
		res[t] = s[i];
		i++;
		t++;
	}
	res[t] = '\0';
	return (res);
}
