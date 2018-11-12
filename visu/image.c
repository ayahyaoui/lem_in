/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 10:56:35 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 17:18:02 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int				ft_get_img(VISU *v)
{
	v->img.img = mlx_new_image(v->mlx, v->win_w, v->win_h);
	v->img.ptr = mlx_get_data_addr(
	v->img.img, &v->img.bpp, &v->img.size, &v->img.endian);
	return (NO_ERR);
}

void			ft_put_to_img(VISU *v, int row, int col, int color)
{
	if (col >= 0 && col <= v->win_h - 1 && row >= 0 && row <= v->win_w - 1)
		*(int *)(v->img.ptr + (row * v->win_w + col) * 4) = color;
}

static void		ft_setcoor(VISU *v, int index, int dest_index)
{
	ft_printf("draw line from (%d %d %d) to (%d %d %d)\n", v->coord.x0, v->coord.y0, v->coord.z0, v->coord.x1, v->coord.y1, v->coord.z1);
//	e->color = e->points[e->row][e->col].color;
	v->coord.x0 = v->ins->room[index].pos.x;
	v->coord.y0 = v->ins->room[index].pos.y;
	v->coord.z0 = v->ins->room[index].pos.z;
	v->coord.x1 = v->ins->room[dest_index].pos.x;
	v->coord.y1 = v->ins->room[dest_index].pos.y;
	v->coord.z1 = v->ins->room[dest_index].pos.z;
}

static void		ft_line_orientndraw(VISU *v, int index, int dest_index)
{
	ft_setcoor(v, index, dest_index);
	ft_drawline(v);
}

void			ft_points_to_img(VISU *v)
{
	int 	row;
	int 	col;

	col = 0;
	while ((unsigned int)col < v->graphe->nb_rooms)
	{
		row = 0;
		while ((unsigned int)row < v->graphe->nb_rooms)
		{
//			ft_printf("display line from %d %d\n", v->ins->room[index].pos.y, v->ins->room[index].pos.x);
			if (v->graphe->map[col][row])
				ft_line_orientndraw(v, col, row);
			++row;
		}
		++col;
	}
}
