/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_fusion_recursive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:58:37 by anyahyao          #+#    #+#             */
/*   Updated: 2018/10/21 16:04:52 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"

/*
**	fait pour une utilisation raisonable
**
*/
static int		setTab(unsigned int t1[][2], unsigned int t2[][2], int i, int j)
{
	t1[i][0] = t2[j][0];
	t1[i][1] = t2[j][1];
	return (1);
}

static void		fusion(unsigned int t1[][2],unsigned int t2[][2],
		 unsigned int tmp[][2], int fin)
{
	int len1;
	int len2;
	int j;
	int k;
	int i;

	len1 = (fin + 1) / 2;
	len2 = fin - len1;
	i = -1;
	j = 0;
	k = 0;
	while (++i < fin)
		if ((j < len1 && t1[j][COST] < t2[k][COST]) || k == len2)
		{
			setTab(tmp, t1, i, j);
			j++;
		}
		else
		{
			setTab(tmp, t2, i, k);
			k++;
		}
	i = -1;
	while (++i < fin)
		setTab(t1, tmp, i, i);
}

static void		tri_fusion(unsigned int t1[][2], unsigned int t2[][2], int fin)
{
	if (fin > 1)
	{
		tri_fusion(t1, t2, (fin + 1) / 2);
		tri_fusion(&t1[(fin + 1) / 2], t2, fin / 2);
		fusion(t1, &t1[(fin + 1) / 2], t2, fin);
	}
}

int				**ft_tri_fusion_recursivecouple(unsigned int t1[][2], int len)
{
	unsigned int t2[9000][2];

	tri_fusion(t1, t2, len);
	return ((int**)t1);
}
