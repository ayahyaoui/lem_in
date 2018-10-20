/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_fusion_recursive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:58:37 by anyahyao          #+#    #+#             */
/*   Updated: 2018/10/20 17:19:08 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
**	fait pour une utilisation raisonable
**
*/
static int		setTab(int **t1, int **t2, int i, int j)
{
	t1[i][0] = t2[j][0];
	t1[i][1] = t2[j][1];
	return (1);
}

static void		fusion(int **t1, int **t2, int **tmp, int fin)
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
		if ((j < len1 && t1[j][1] < t2[k][1]) || k == len2)
		{
			setTab(tmp, t1, i, j);
			j++;
		}
		else
		{
			setTab(tmp, t1, i, j);
			k++;
		}
	i = -1;
	while (++i < fin)
		setTab(t1, tmp, i, i);
}

static void		tri_fusion(int **t1, int **t2, int fin)
{
	if (fin > 1)
	{
		tri_fusion(t1, t2, (fin + 1) / 2);
		tri_fusion(&t1[(fin + 1) / 2], t2, fin / 2);
		fusion(t1, &t1[(fin + 1) / 2], t2, fin);
	}
}

int				**ft_tri_fusion_recursivecouple(int **t1, int len)
{
	int t2[9000][2];

	//t2 = malloc(sizeof(int) * (len + 1));
	tri_fusion(t1, (int **)t2, len);
	return (t1);
}
