/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affiche_string_dim2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 06:04:20 by anyahyao          #+#    #+#             */
/*   Updated: 2018/08/01 06:09:51 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_affiche_string_dim2(char **av, int ac)
{
	int i;

	i = -1;
	while (++i < ac)
	{
		ft_putstr(av[i]);
		ft_putchar('\n');
	}
}
