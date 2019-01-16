/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:25:06 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/16 22:25:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_free_strtab(char ***tab)
{
	char	**tmp;

	if (!*tab)
		return ;
	tmp = *tab;
	while (tmp && *tmp)
	{
		ft_strdel(tmp);
		++tmp;
	}
	ft_memdel((void **)tab);
}
