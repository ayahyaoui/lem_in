/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_transformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:39:45 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/13 17:46:09 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

static void	ft_merge_transformations(VISU *v, double (*m)[4][4], int index)
{
	static double	temp1[4][4];
	static double	temp2[4][4];
	static void		(*trans[TRANS])(VISU *v, double (*trans)[4][4]) = {
		&ft_getm_center_to_origin,
		&ft_getm_scaledown,
		&ft_getm_rot,

//	&ft_getm_scaleup,
		
		&ft_getm_zoom,
		&ft_getm_setcenter,
		&ft_getm_move,
	};

	if (index == 6)
		return ;
	ft_44mcpy(&temp1, *m);
	trans[index](v, &temp2);
	ft_44mtrxmtrx_mul(m, temp2, temp1);
		
	ft_merge_transformations(v, m, index + 1);
}
/*
static void	ft_initialize_height(ENV *e, double (*m)[4][4], int index)
{
	e->ins->room[index].pos = ft_4mtrxvect_mul(m, &e->ins->room[index].pos);
	e->ins->room[index].pos.z = 20;
}*/
/*
   static void	ft_apply_height_and_color(VISU *v, int row, int col)
   {
   double m_height[4][4];

   if (v->points[row][col].row_size && v->points[row][col].p.z && v->newheight)
   {
   ft_getm_height(v, &m_height);
   v->points[row][col].p =
   ft_4mtrxvect_mul(&m_height, &v->points[row][col].p);
   }
   if (v->uinput.color_map)
   v->points[row][col].color =
   ft_get_altcolor(v, v->points[row][col].init.z);
   else
   v->points[row][col].color =
   ft_get_nicecolor(v, v->points[row][col].init.z);
   }
   */

static int	ft_apply_transformation(VISU *v, double (*m)[4][4])
{
	int index;

	index = -1;
	while ((unsigned int)++index < v->graphe->nb_rooms)
	{
//		printf("before TRANFORM! posx = %f posy = %f\n", v->ins->room[index].pos.x, v->ins->room[index].pos.y);
		v->ins->room[index].pos = ft_4mtrxvect_mul(m, &v->ins->room[index].pos);
//		printf("after TRANFORM! posx = %f posy = %f\n", v->ins->room[index].pos.x, v->ins->room[index].pos.y);
	}
	return (0);
}


int		ft_setextremes(VISU *v)
{
//	v->min.x = 1000;
//	v->min.y = 1000;
//	v->max.x = 0;
//	v->max.y = 0;

	int index;

	index = -1;
	ft_4vinit(&v->min, INT_MAX, INT_MAX, 0);
	ft_4vinit(&v->max, INT_MIN, INT_MIN, 0);
//	printf("before set extremes minx = %f, maxx = %f miny = %f maxy = %f\n", v->min.x, v->max.x, v->min.y, v->max.y);
	while ((unsigned int)++index < v->graphe->nb_rooms)
	{
//		printf("room pos.x = %f room pos.y = %f\n", v->ins->room[index].pos.x, v->ins->room[index].pos.y);
		if (v->ins->room[index].pos.x < v->min.x)
			v->min.x = v->ins->room[index].pos.x;
		else if (v->ins->room[index].pos.x > v->max.x)
			v->max.x = v->ins->room[index].pos.x;
		if (v->ins->room[index].pos.y < v->min.y)
			v->min.y = v->ins->room[index].pos.y;
		else if (v->ins->room[index].pos.y > v->max.y)
			v->max.y = v->ins->room[index].pos.y;
	}
	if (!v->coef)
		v->coef = v->win_w / (v->max.x - v->min.x) * 0.5;
	else
		v->coef = 1;
//	printf("temp coef = %f\n", v->coef);
//	if (v->max.y - v->min.y > v->coef)
//		v->coef = v->max.y - v->min.y;
//	printf("minx = %f, maxx = %f miny = %f maxy = %f | coef = %f\n", v->min.x, v->max.x, v->min.y, v->max.y, v->coef);
	return (0);
}

void		change_val(VISU *v)
{
	int	index;
//	printf("win_w = %d prev coef = %f\n", v->win_w, v->coef);
	v->coef = v->win_w / v->coef * 0.5;
	
	index = 0;
//	printf("coef = %f\n", v->coef);
	while ((unsigned int)index < v->graphe->nb_rooms)
	{
//		printf("before x = %lf y = %lf\n", v->ins->room[index].pos.x, v->ins->room[index].pos.y);
			v->ins->room[index].pos.x -= (v->min.x + (v->max.x - v->min.x) * 0.5);
			v->ins->room[index].pos.y -= (v->min.y + (v->max.y - v->min.y) * 0.5);
			v->ins->room[index].pos.x *= v->coef;
			v->ins->room[index].pos.y *= v->coef;
			v->ins->room[index].pos.x += (v->win_w * 0.5);
			v->ins->room[index].pos.y += (v->win_h * 0.5);
//		if (v->max.x <= WIN_W * 0.5)
//		if (v->min.x >= WIN_W * 0.5)
//			v->ins->room[index].pos.x -= ((v->min.x - v->win_w * 0.5) + (v->max.x - v->min.x) + 0.5);
//		if (v->max.y <= WIN_H * 0.5)
//			v->ins->room[index].pos.y += ((v->win_h * 0.5 - v->max.y) + (v->max.y - v->min.y) * 0.5);
//		if (v->min.y >= WIN_H * 0.5)
//			v->ins->room[index].pos.y -= ((v->min.y - v->win_h * 0.5) + (v->max.y - v->min.y) * 0.5);
//		printf("after x = %lf y = %lf\n", v->ins->room[index].pos.x, v->ins->room[index].pos.y);

//		display_square(v, index, 10, 0xFFFFFF);
		++index;
	}
	ft_setextremes(v);
//		printf("after scale x = %lf y = %lf\n", v->ins->room[index].pos.x, v->ins->room[index].pos.y);
//		v->ins->room[index].pos.x *= v->coef; 
//		v->ins->room[index].pos.y *= v->coef; 
}

void		add_names(VISU *v)
{
	int	index;

	index = 0;
	while ((unsigned int)index < v->graphe->nb_rooms)
	{
		mlx_string_put(v->mlx, v->win, v->ins->room[index].pos.x, v->ins->room[index].pos.y, 0x0000FF, v->ins->room[index].name);
		++index;
	}
}


void		display_rooms(VISU *v)
{
	int index[2];
	int	i;

	i = -1;
	while ((unsigned int)++i < v->graphe->nb_rooms)
	{
		index[0] = i;
		index[1] = i;
		display_square(v, (int *)&index, 10, COL_ROOM);
	}
}



int			ft_transform_points(VISU *v)
{
	double		ftrans[4][4];

	ft_44minit(&ftrans, 1);
//	ft_printf("TRANSFORM POINTS\n");
	ft_setextremes(v);
	ft_merge_transformations(v, &ftrans, 0);
	ft_apply_transformation(v, &ftrans);
	return (1);
}
