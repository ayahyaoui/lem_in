/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_inttab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:26:20 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 22:26:36 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_inttab(int ***tab, int size)
{
	int	i;

	i = -1;
	if (tab && !*tab)
		return ;
	while (++i < size && (*tab)[i])
		ft_memdel((void **)&(*tab)[i]);
	ft_memdel((void **)tab);
}
