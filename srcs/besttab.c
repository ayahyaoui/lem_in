/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   besttab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 21:58:22 by anyahyao          #+#    #+#             */
/*   Updated: 2019/01/14 23:09:39 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"



t_tab	***allowBestTab(int nb_path)
{
	t_tab ***besttab = 0x0;

	if (!(besttab = (t_tab***)ft_memalloc(sizeof(t_tab**) * (nb_path + 1))))
		return (0x0);
	return (besttab);
}

int		addPath(t_node *node, t_graphe *g, t_tab *t)
{
	int pos;

	if (node->value == g->start)
	{
		t->tab[0] = g->start;
		return 1;
	}
	pos = addPath(g->node[node->parent], g, t);
	t->tab[pos] = node->value;
	return pos + 1;
}

void	get_infos_allow_tab(t_graphe *g,int *nb_path, int *sizeMax)
{
	int i;
	t_node *node;

	ft_bzero(g->capacite, sizeof(int) * g->nb_rooms);
	i = -1;
	*nb_path =  (g->start_next_to_end == 1) ? 1 : 0;
	*sizeMax = (g->start_next_to_end == 1) ? 2 : -1;
	while (++i < (int)g->nb_rooms)
	{
		if (g->map[i][g->end] > 0 && g->node[i]->parent >= 0)
		{
			node = g->node[i];
			g->capacite[i]+=1;
			while (node->value != g->start)
			{
				node = g->node[node->parent];
				g->capacite[i]+=1;
			}
			if (g->capacite[i] > *sizeMax)
				*sizeMax = g->capacite[i];
			*nb_path = *nb_path + 1;
		}
	}
}

t_tab	**allowTab(t_graphe *g, t_tab **besttab)
{
	int i;
	int j;
	int sizeMax;

	j = 0;
	get_infos_allow_tab(g, &j, &sizeMax);
	if (!(besttab = ft_memalloc(sizeof(t_tab *) * (j  + 2))))
		return (0x0);
	i = -1;
	while (++i < j)
	{
		if (!(besttab[i] = (t_tab*)ft_memalloc(sizeof(t_tab))))
			return (0x0);
		if (!(besttab[i]->tab = ft_memalloc(sizeof(int) * (sizeMax + 2))))
			return (0x0);
	}
	besttab[j] = 0x0;
	return (besttab);
}

void	placeValueInTab(int *tab, int value, int pos)
{
	int tmp;

	while (tab[pos] >=  0)
	{
		tmp = tab[pos];
		tab[pos] = value;
		value = tmp;
		pos++;
	}
	tab[pos] = value;
}

int		SortPath(t_graphe *g)
{
	int i;
	int j;

	ft_memset(g->previous, -1,sizeof(int) * g->nb_rooms);
	i = -1;
	while (++i < (int)g->nb_rooms)
	{
		if (g->capacite[i] > 0)
		{
			j = 0;
			while (g->previous[j] >= 0
					&& g->capacite[i] > g->capacite[g->previous[j]])
				j++;
			//ft_printf("val = %d pos = %d et j = %d", g->capacite[i], i, j);
			placeValueInTab(g->previous, i, j);
		}
	}
	return (1);
}

void					*ft_realloc(void *previous, size_t t, size_t len_src)
{
	unsigned char *dest;

	if (!(dest = (unsigned char *)malloc(sizeof(char) * t)))
		return (0x0);
	dest = ft_memcpy(dest, previous, len_src);
	ft_memdel(&previous);
	return (dest);
}

void	ft_add_exeption(t_graphe *g, t_tab ***besttab, int nb_path)
{
	if (g->start_next_to_end)
	{
		besttab[nb_path][0]->length = 2;
		besttab[nb_path][0]->tab[1] = g->end;
	}
}

t_tab	***registerPath(t_graphe *g, int nb_path, t_tab ***besttab)
{
	int i;
	int k;

	i = -1;
	if (nb_path > 0 &&  (nb_path % PATH_SIZE) == 0)
		if (!(besttab = (t_tab***)ft_realloc((char*)besttab,
	sizeof(t_tab**) * (nb_path + PATH_SIZE + 1), sizeof(t_tab **) * (nb_path)
						)))
			return (0x0);
	if (!(besttab[nb_path] = allowTab(g, besttab[nb_path])))
		return (0x0);
	i = 0;
	SortPath(g);
	k = g->start_next_to_end;
	ft_add_exeption(g, besttab, nb_path);
	while (g->previous[i] >= 0)
	{
		besttab[nb_path][i + k]->length = 
			addPath(g->node[g->previous[i]], g, besttab[nb_path][i + k]) + 1;
		besttab[nb_path][i + k]->tab[besttab[nb_path][i + k]->length - 1] = g->end;
		++i;
	}
	g->nb_paths++;
	return besttab;
}
