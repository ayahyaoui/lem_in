/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tri_fusion_recursive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:58:37 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/22 18:21:59 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fusion(int *t1, int *t2, int *tmp, int fin)
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
		if ((j < len1 && t1[j] < t2[k]) || k == len2)
		{
			tmp[i] = t1[j];
			j++;
		}
		else
		{
			tmp[i] = t2[k];
			k++;
		}
	i = -1;
	while (++i < fin)
		t1[i] = tmp[i];
}

void	tri_fusion(int *t1, int *t2, int fin)
{
	if (fin > 1)
	{
		tri_fusion(t1, t2, (fin + 1) / 2);
		tri_fusion(&t1[(fin + 1) / 2], t2, fin / 2);
		fusion(t1, &t1[(fin + 1) / 2], t2, fin);
	}
}

int		*ft_tri_fusion_recursive(int *t1, int len)
{
	int *t2;

	t2 = malloc(sizeof(int) * (len + 1));
	tri_fusion(t1, t2, len);
	free(t2);
	return (t1);
}
