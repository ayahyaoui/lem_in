/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_points.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:39:45 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 13:58:32 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <limits.h>

/*
** iterate through transformation matrices and multiply into one single global
** transformation matrix for future use
** Input: global matrix for transformation, int index for scanning matrix table
*/

static void		ft_merge_transformations(VISU *v, double (*m)[4][4], int index)
{
	static double	temp1[4][4];
	static double	temp2[4][4];
	static void		(*trans[TRANS])(VISU *v, double (*trans)[4][4]) = {
		&ft_getm_center_to_origin,
		&ft_getm_scaledown,
		&ft_getm_rot,
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
** pass all room coordinates through the global transformation matrix
** Input: transformation matrix
*/

static void		ft_apply_transformation(VISU *v, double (*m)[4][4])
{
	int index;

	index = -1;
	while ((unsigned int)++index < v->graphe->nb_rooms)
		v->ins->room[index].pos = ft_4mtrxvect_mul(m, &v->ins->room[index].pos);
}

/*
** Set extreme anthill values to fit in display screen
*/

static void		ft_setextremes(VISU *v)
{
	int index;

	index = -1;
	ft_4vinit(&v->min, INT_MAX, INT_MAX, 0);
	ft_4vinit(&v->max, INT_MIN, INT_MIN, 0);
	while ((unsigned int)++index < v->graphe->nb_rooms)
	{
		if (v->ins->room[index].pos.x < v->min.x)
			v->min.x = v->ins->room[index].pos.x;
		else if (v->ins->room[index].pos.x > v->max.x)
			v->max.x = v->ins->room[index].pos.x;
		if (v->ins->room[index].pos.y < v->min.y)
			v->min.y = v->ins->room[index].pos.y;
		else if (v->ins->room[index].pos.y > v->max.y)
			v->max.y = v->ins->room[index].pos.y;
	}
	v->coef = v->coef ? 1 : v->win_w / (v->max.x - v->min.x) * 0.5;
}

/*
** transform room coordinates, taking into account desired size of anthill and
** desired transformations (rotation, movement, zoom, etc.))
*/

void			ft_transform_points(VISU *v)
{
	double		ftrans[4][4];

	ft_44minit(&ftrans, 1);
	ft_setextremes(v);
	ft_merge_transformations(v, &ftrans, 0);
	ft_apply_transformation(v, &ftrans);
}
