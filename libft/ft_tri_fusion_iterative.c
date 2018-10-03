/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_fusion_iterative.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:57:55 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/27 08:04:25 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	petit_fusion(int *t, int *tmp, int fu, int len)
{
	int i;
	int j;
	int k;
	int fuu;

	if (len < fu)
	{
		while (--len >= 0)
			tmp[len] = t[len];
		return ;
	}
	fuu = fu;
	fu *= 2;
	k = fuu;
	j = 0;
	i = -1;
	len = (len > fu) ? fu : len;
	while (++i < len)
		if ((j < fuu && t[j] < t[k]) || k == len)
			tmp[i] = t[j++];
		else
			tmp[i] = t[k++];
}

int		*nouv_algo_de_ouf(int *t1, int *t2, int len)
{
	int *tmp;
	int i;
	int j;

	i = 2;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			petit_fusion(&t1[j], &t2[j], i / 2, len - j);
			j += i;
		}
		i *= 2;
		tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	petit_fusion(t1, t2, i / 2, len);
	return (t2);
}

void	ft_tri_fusion_iterative(int *t1, int len)
{
	int *t2;
	int i;

	i = -1;
	t2 = malloc(sizeof(int) * (len + 1));
	nouv_algo_de_ouf(t1, t2, len);
	if (!ft_issort(t1, len))
		while (++i < len)
			t1[i] = t2[i];
	free(t2);
}
