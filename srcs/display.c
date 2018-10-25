/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:04:49 by emuckens          #+#    #+#             */
/*   Updated: 2018/10/21 00:51:34 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		display_adj_mtrx(int **tab, int size)
{
	int	i;
	int	j;	

	i = -1;
	ft_printf("\t | ", i);
	while (++i < size)
		ft_printf("%d ", i);
	ft_printf("\n");
	j = -1;
	while (++j < size)
	{
		i = -1;
		ft_printf("%d\t | ", j);
		while (++i < size) 
			ft_printf("%d ", tab[j][i]);
		ft_printf("\n");
	}

}


void		display_anthill(t_list *anthill)
{
	t_list *tmp;

	tmp = anthill;
	while (tmp)
	{
		ft_printf("%s\n", (char *)(tmp->content));
		tmp = tmp->next;
	}
}
