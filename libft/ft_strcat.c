/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 20:11:55 by anyahyao          #+#    #+#             */
/*   Updated: 2018/03/13 20:53:24 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfreecat(char *s, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (s[i])
		i++;
	while (str[++j])
	{
		s[i] = str[j];
		i++;
	}
	s[i] = '\0';
	free(str);
	return (s);
}

char	*ft_strcat(char *s, const char *str)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (s[i])
		i++;
	while (str[++j])
	{
		s[i] = str[j];
		i++;
	}
	s[i] = '\0';
	return (s);
}
