/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:20:23 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/13 17:22:07 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				*create_tab(int taille, int val);
char			**create_double_tab(int taille, int val);

char			**create_double_tab(int taille, int val)
{
	char **map;
	int i;
	int j;

	i = 0;
	map = (char **)malloc(sizeof(char *) * taille);
	while (i < taille)
	{
		map[i] = (char *)malloc(sizeof(char) * taille);
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


	tab = (int *)malloc(sizeof(int) * taille);
	i = -1;
	while (++i < taille)
		tab[i] = val;
	return (tab);
}

