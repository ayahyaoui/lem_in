/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_center.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 21:20:34 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/19 20:10:47 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdio.h>

void	ft_getm_setcenter(VISU *v, double (*dest)[4][4])
{
	v->shift.x = v->win_w * 0.5;
	v->shift.y = v->win_h * 0.5;
	v->shift.z = 0;
	ft_getm_trans(v, dest);
}

void	ft_getm_center_to_origin(VISU *v, double (*dest)[4][4])
{
	ft_44minit(dest, 1);
	ft_printf("center = %d\n", v->center);
	printf("1 max x = %f min x = %f shift x = %f max y = %f min y = %f shift y = %f\n", v->max.x, v->min.x, v->shift.x, v->max.y, v->min.y, v->shift.x);
	v->shift.x = -(v->max.x - v->min.x) * 0.5 -  v->min.x;
	v->shift.y = -(v->max.y - v->min.y) * 0.5 -  v->min.y;
	printf("2 max x = %f min x = %f shift x = %f max y = %f min y = %f shift y = %f\n", v->max.x, v->min.x, v->shift.x, v->max.y, v->min.y, v->shift.y);
	ft_getm_trans(v, dest);
}
