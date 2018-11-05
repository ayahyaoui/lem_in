/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 17:57:51 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/04 20:29:20 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			add_ant(t_graphe *g, t_tab ***best_tab, int nb_ant);

int			count_dim3(t_tab ***best_tab)
{
	int i;

	i = 0;
	if (!best_tab)
		return (-1);
	while (best_tab[i])
		i++;
	return (i);
}

int		maxants_ntour(t_tab **best_tab, int nb_tour)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	if (!best_tab)
		return (-1);
	while (best_tab[++i])
		res += ft_maxint(0, nb_tour - (best_tab[i]->length - 2));
	ft_printf("max = %d et len = %d en nb_tour %d ",res, best_tab[0]->length, nb_tour);
	return (res);
}

int		placeant(t_tab **best_tab, int nb_ant)
{
	int i;

	i = 0;
	if (!best_tab)
		return (-1);
	best_tab[0]->tab[0] = nb_ant;
	while (best_tab[++i])
		best_tab[i]->tab[0] = 0;
	return (1);
}

// pos > 0
int		count_ants(t_graphe *g, t_tab ***best_tab, int nb_ant, int pos)
{

	int i;
//	int j;

//	i = maxant_ntour(best_tab[pos]);
//	j = maxant_ntour(best_tab[pos - 1]);
	i = 1;
//	j = 0;
	(void)g;
	while (maxants_ntour(best_tab[pos], i) <=
			maxants_ntour(best_tab[pos - 1], i) && i < nb_ant)
	{
		i++;
		ft_putstr("\n");
	}
//	int ret = maxants_ntour(best_tab[pos], i);
	placeant(best_tab[pos], i);
	return (i);
}


int			add_ant(t_graphe *g, t_tab ***best_tab, int nb_ant)
{
	int lim;

	if ((lim = count_dim3(best_tab)) == -1)
		return (-1);
	while (nb_ant > 0 && --lim > 0)
	{
		nb_ant -= count_ants(g, best_tab, nb_ant, lim);
	}
	best_tab[0][0]->tab[0] = nb_ant;

	return (1);
}

