/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fusion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 17:52:48 by anyahyao          #+#    #+#             */
/*   Updated: 2018/11/02 18:07:39 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			valueisinfusion(t_fusion *fusion, int value);
void		infos(t_fusion *f);
int		getfusionpath(t_breakdown *b, int *res, unsigned int val, int cost);
int		fusion_path(t_fusion *fusion, unsigned int tab[2], t_breakdown *copy);
void	ft_swapPointeur(t_fusion **a, t_fusion **b);

void	ft_swapPointeur(t_fusion **a, t_fusion **b)
{
	t_fusion *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		fusion_path(t_fusion *fusion, unsigned int tab[2], t_breakdown *copy)
{
	t_breakdown	*src;
	int			i;

	i = -1;
	src = fusion->fusion[fusion->nb_path];
	src->value = tab[VALUE] + copy->value;
	src->cost = tab[COST] + copy->cost;
	src->len = copy->len + 1;
	while (++i < copy->len)
		src->breakdown[i] = copy->breakdown[i];
	src->breakdown[copy->len] = tab[VALUE];
	fusion->nb_path++;
	return (1);
}


int		getfusionpath(t_breakdown *b, int *res, unsigned int val, int cost)
{
	int		i;

	i = -1;
	//ft_printf("//%d et %d", b->value, val);
	while (++i < b->len)
	{
		//ft_printf("getfusionpath  %d",b->breakdown[i]);
		res[i] = b->breakdown[i];
	}
		res[i] = val;
	return (cost);
}

void		infos(t_fusion *f)
{
	int j;
	ft_putstr("                       fus\n");
	ft_printf("nombre de chemin <%u>, et nombre de voie en parallele (%u)\n",
			f->nb_path,f->altern);
	int i = -1;
	while (++i < f->nb_path)
	{
		ft_printf("val = %u cout = %u et taille %u",
				f->fusion[i]->value, f->fusion[i]->cost, f->fusion[i]->len);
		j = -1;
		while (++j < f->fusion[i]->len)
			ft_printf("(%d)", f->fusion[i]->breakdown[j]);
		ft_printf("\n");
	}
}

int			valueisinfusion(t_fusion *fusion, int value)
{
	int i;
	i = -1;
	if (!fusion)
		return (0);
	while (++i < fusion->nb_path)
		if (value == fusion->fusion[i]->value)
			return (1);
	return (0);
}


