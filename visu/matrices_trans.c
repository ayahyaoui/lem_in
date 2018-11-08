/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_trans.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:51:12 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 18:59:38 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdio.h>
/*
void	ft_getm_height(VISU *v, double (*dest)[4][4])
{
	ft_44minit(dest, 1);
	(*dest)[2][3] = v->uinput.height;
}*/
/*
void	ft_getm_heightinit(VISU *v, double (*dest)[4][4])
{
	ft_44minit(dest, 1);
	if (v->maxheight > 55)
		(*dest)[2][2] = 55.0 / v->maxheight;
	else if (e->minheight < -55)
		(*dest)[2][2] = 55.0 / e->minheight;
	e->minheight *= (*dest)[2][2];
	e->maxheight *= (*dest)[2][2];
}
*/
void	ft_getm_move(VISU *v, double (*dest)[4][4])
{
	ft_printf("move hor = %d move ver = %d\n", v->uinput.mv_hor, v->uinput.mv_ver);
	ft_4ivinit(&v->shift, v->uinput.mv_hor, v->uinput.mv_ver, 0);
	v->center = 0;
	ft_getm_trans(v, dest);
}

void	ft_getm_trans(VISU *v, double (*dest)[4][4])
{
	ft_printf("shift x = %d shift y = %d\n", v->shift.x, v->shift.y);
	ft_44minit(dest, 1);
	(*dest)[0][3] = v->shift.x;
	(*dest)[1][3] = v->shift.y;
	(*dest)[2][3] = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			printf("%f ", (*dest)[i][j]);
		printf("\n");
	}

}
