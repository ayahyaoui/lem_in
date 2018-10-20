/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 20:31:05 by emuckens          #+#    #+#             */
/*   Updated: 2018/06/26 19:46:19 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (!new)
		return ;
	if (*alst == NULL)
	{
//		if (*alst == NULL)
//			ft_printf("tjr null??\n");
		new->next = *(alst);
//		ft_printf("no ele in lst\n");
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	ft_printf("tmp val = %d tmp next val %d\n", *(int *)tmp->content, *(int *)tmp->next->content);
}
