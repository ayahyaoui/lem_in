/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:20:23 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/15 17:49:18 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				**create_double_int_tab(int taille, int val)
{
	int **map;
	int i;
	int j;

	i = 0;
	map = (int **)ft_memalloc(sizeof(int *) * taille);
	while (i < taille)
	{
		map[i] = (int *)ft_memalloc(sizeof(int) * taille);
		j = 0;
		while (j < taille)
		{
			map[i][j] = val;
			j++;
		}
		i++;
	}
	return (map);
}

int				*create_tab(int taille, int val)
{
	int		*tab;
	int		i;

	if (!(tab = (int *)ft_memalloc(sizeof(int) * taille)))
		return (0x0);
	i = -1;
	while (++i < taille)
		tab[i] = val;
	return (tab);
}

t_node			*create_node(int value)
{
	t_node *node;

	if (!(node = ft_memalloc(sizeof(t_node))))
		return (0x0);
	node->parent = -1;
	node->previous = -1;
	node->value = value;
	return (node);
}
