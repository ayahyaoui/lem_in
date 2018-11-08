/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_center.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 21:20:34 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 18:33:30 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ft_getm_setcenter(VISU *v, double (*dest)[4][4])
{
	ft_printf("winw = %d WINW = %d winh = %d WINH = %d\n", v->win_w, WIN_W, v->win_h, WIN_H);
	v->shift.x = v->win_w * 0.5;
	v->shift.y = v->win_h * 0.5;
	v->shift.z = 0;
	ft_getm_trans(v, dest);
//	v->center = 0;
}

void	ft_getm_center_to_origin(VISU *v, double (*dest)[4][4])
{
	ft_44minit(dest, 1);
	ft_printf("center = %d\n", v->center);
//	if (v->max.x <= WIN_W * 0.5)
//		v->shift.x = (WIN_W * 0.5 - v->max.x) + (v->max.x - v->min.x);
//	else	
//		v->shift.x = -(WIN_W * 0.5 - v->min.x) - (v->max.x - v->min.x);
//	if (v->max.y <= WIN_H * 0.5)
//		v->shift.y = (WIN_H * 0.5 - v->max.y) + (v->max.y - v->min.y);
//	else	
//		v->shift.y = -(WIN_H * 0.5 - v->min.y) - (v->max.y - v->min.y);
		
		
	if (!v->center)
	{	
		v->shift.x = -(v->max.x - v->min.x) * 0.5 - v->min.x;
		v->shift.y = -(v->max.y - v->min.y) * 0.5 - v->min.y;
		ft_printf("max x = %d min x = %d shift x = %d max y = %d min y = %d shift y = %d\n", v->max.x, v->min.x, v->max.y, v->min.y, v->shift.x, v->shift.y);
//	v->shift.z = 0;

	}
		else
	{
		v->shift.x = 0;
		v->shift.y = 0;
	}
	
//	v->center = 1;
	ft_getm_trans(v, dest);
}
