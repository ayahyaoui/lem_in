/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:34:11 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 06:04:54 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		is_number(char *str)
{
	int		i;
	
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != '-')|| ((str[i] == '-') && i))
			return (0);
		++i;
	}
	return (1);
}

t_list	*ft_lstval(t_list *l, int index)
{
	int i;
	t_list *tmp;

	i = 0;
	tmp = l;
	while (i < index)
	{
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}
