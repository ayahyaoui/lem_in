/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:20:23 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/17 00:20:32 by emuckens         ###   ########.fr       */
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

t_tab			***create_besttab(int nb_path)
{
	t_tab ***besttab;

	if (!(besttab = (t_tab***)ft_memalloc(sizeof(t_tab**) * (nb_path + 1))))
		return (0x0);
	return (besttab);
}

/*
** Set up environment
** Return error code if malloc error, else return 1
*/

int				set_env(ENV *e)
{
	if (!(e->ins = (t_input *)ft_memalloc(sizeof(t_input))))
		return (ERR_ALLOC);
	if (!(e->graphe = (t_graphe *)ft_memalloc(sizeof(t_graphe))))
		return (ERR_ALLOC);
	e->graphe->start = -1;
	e->graphe->end = -1;
	e->max_paths = -1;
	return (1);
}
