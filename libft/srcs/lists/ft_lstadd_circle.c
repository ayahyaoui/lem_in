/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 20:31:05 by emuckens          #+#    #+#             */
/*   Updated: 2017/12/22 11:32:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../../includes/checker.h"
void	ft_lstaddcircle(t_list **alst, t_list *new)
{
	t_list *tmp;

	tmp = *alst;
	if (!new)
		return ;
	new->next = *alst;
	*alst = new;
	ft_putcnl('A');
	if (tmp->next != *alst)
	{
/	ft_putcnl('B');
	while (tmp != *alst)
	{
	
//	ft_putcnl('B');
	ft_printf("check tmp = %d and next %d\n", ((ITEM *)(tmp->content))->val, ((ITEM *)(tmp->next->content))->val);
		tmp = tmp->next;
	}
	}
	if (tmp)
	tmp->next = new;
	ft_putcnl('C');
}
