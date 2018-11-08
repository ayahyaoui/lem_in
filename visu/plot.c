/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 18:38:49 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 15:18:24 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	ft_progress_on_axis(int *coord, double *error, int step, int delta)
{
	*coord += step;
	*error += delta;
}

static void	ft_inner_drawline(VISU *v, double error, int *step)
{
	int x;
	int y;

	x = v->coord.x0;
	y = v->coord.y0;
	if (v->coord.dx >= v->coord.dy)
		while (ft_abs(x - v->coord.x1))
		{
			ft_put_to_img(v, (size_t)y, (size_t)x, v->color);
			error -= v->coord.dy;
			if (error < 0)
				ft_progress_on_axis(&y, &error, step[Y], v->coord.dx);
			x += step[X];
		}
	else
		while (ft_abs(y - v->coord.y1))
		{
			ft_put_to_img(v, (size_t)y, (size_t)x, v->color);
			error -= v->coord.dx;
			if (error < 0)
				ft_progress_on_axis(&x, &error, step[X], v->coord.dy);
			y += step[Y];
		}
	ft_put_to_img(v, v->coord.y1, v->coord.x1, v->color);
}

void		ft_drawline(VISU *v)
{
	double	error;
	int		step[2];

	v->coord.dx = ft_abs(v->coord.x1 - v->coord.x0);
	v->coord.dy = ft_abs(v->coord.y1 - v->coord.y0);
	if (v->coord.dx > v->coord.dy)
		error = (double)((double)v->coord.dx * 0.5);
	else
		error = (double)((double)v->coord.dy * 0.5);
	step[X] = v->coord.x1 >= v->coord.x0 ? 1 : -1;
	step[Y] = v->coord.y1 >= v->coord.y0 ? 1 : -1;
	ft_inner_drawline(v, error, step);
}
