/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/13 19:00:06 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdio.h>


void		draw_ant_legs(VISU *v, int *ant, int scale, int option)
{
	double x;
	double  y;

	x = v->ins->room[ant[CURRENT]].pos.x;
	y = v->ins->room[ant[CURRENT]].pos.y;
//	int x;
//	int y;
//	t_4vect delta;
//
//	x = v->ins->room[ant[CURRENT]].pos.x;
//	delta.x = (v->ins->room[ant[NEXT]].pos.x - x) / SPEED;
//	x += delta.x;
//	y = v->ins->room[ant[CURRENT]].pos.x;
//	delta.y = (v->ins->room[ant[NEXT]].pos.y - y) / SPEED;
//	y += delta.y;
//
//	x = v->ins->room[index].pos.x;
//	y = v->ins->room[index].pos.y;
	(void)ant;
	v->coord.x0 = x + (option ? v->delta.x + scale : v->delta.x - scale);
	v->coord.x0 -= 2;
	v->coord.y0 = y + v->delta.y - scale;
	v->coord.x1 = x + (option ? v->delta.x - scale : v->delta.x + scale);
	v->coord.x1 -= 2;
	v->coord.y1 = y + v->delta.y + scale;
	ft_drawline(v);
}

void		display_ant(VISU *v, int *ant, int scale)
{
	double x;
	double  y;

	x = v->ins->room[ant[CURRENT]].pos.x;
	y = v->ins->room[ant[CURRENT]].pos.y;
	if (!ant)
		return ;
//	printf("display ant going from room %d to room %d, v->delta x = %lf, v->delta y = %lf\n", ant[CURRENT], ant[NEXT], v->delta.x, v->delta.y);
//	y += delta.y;
	if (scale < 5)
		scale = 5;
	v->color = COL_ANT;
	display_square(v, ant, -2, COL_ANT);
	v->coord.x0 = x + v->delta.x - 2 * scale + 2;
	v->coord.y0 = y + v->delta.y;
	v->coord.x1 = x + v->delta.x + 4;
	v->coord.y1 = y + v->delta.y;
	ft_drawline(v);
	v->coord.x0 = x + v->delta.x - 2;
	v->coord.y0 = y + v->delta.y - scale;
	v->coord.x1 = x + v->delta.x - 2;
	v->coord.y1 = y + v->delta.y + scale;
	ft_drawline(v);
	draw_ant_legs(v, ant, scale, 0);
	draw_ant_legs(v, ant, scale, 1);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	display_ant_names(v);
}

void		display_square(VISU *v, int *ant, int width, int color)
{
	int col;
	int row;
	double x;
	double y;

	x = v->ins->room[ant[CURRENT]].pos.x;
	v->delta.x = v->step * (v->ins->room[ant[NEXT]].pos.x - x) / 50.0;
	y = v->ins->room[ant[CURRENT]].pos.y;
	v->delta.y = v->step * (v->ins->room[ant[NEXT]].pos.y - y) / 50.0;
	if (width < 0)
	{
		x += v->delta.x;
		y += v->delta.y;
	}
	if (width < 0)
	{
		width *= -1;
		x += 5;
	}
	col = x - width;
	while (col < x + width)
	{
		row = y - width;
		while (row < y + width)
		{
			ft_put_to_img(v, row, col, color);
			++row;
		}
		++col;	
	}
}

int		read_moves(VISU *v, char *line, int room)
{
	char **split;
	char **antsplit;
	int ant;
	int num;

	if (line)
		ft_printf("in read moves, line = %s\n", line);
	if (!(split = ft_strsplit(line, ' ')))
		return (ERR_READ);
	ant = -1;
	if (!v || !v->ins)
		return (-1);
	ant = 0;
	while (ant <= v->ins->nb_ants)
	{
		if (!(antsplit = ft_strsplit(split[ant], '-')))
			return (ERR_READ);
		num = ft_atoi(antsplit[0] + 1);

		v->ants[num - 1][CURRENT] = v->ants[num - 1][NEXT];
		if (v->ants[num - 1][CURRENT] != v->graphe->end)
			v->ants[num - 1][room] = get_room_index(v, antsplit[1], ft_strlen(antsplit[1]));
		else
			v->ants[num - 1][CURRENT] = -1;
//			{
//
//			}
		if (v->ants[num - 1][NEXT] != -1 && v->ants[num - 1][CURRENT] == -1)
			v->ants[num - 1][CURRENT] = v->graphe->start;
		printf("ant # %d | current = %d (%lf, %lf)  next = %d (%lf, %lf) \n", num, v->ants[num - 1][0], v->ins->room[v->ants[num - 1][0]].pos.x, v->ins->room[v->ants[num - 1][0]].pos.y, v->ants[num - 1][1], v->ins->room[v->ants[num - 1][1]].pos.x, v->ins->room[v->ants[num - 1][1]].pos.y);
		ft_strdel(&antsplit[0]);
		ft_strdel(&antsplit[1]);
		ft_memdel((void **)&antsplit);
		ft_strdel(&split[ant]);
		++ant;
	}
	ft_memdel((void **)&split);
	return (0);
}


void		display_ant_names(VISU *v)
{
	int ant;
	double x;
	double y;
	double deltax;
	double deltay;

	ant = 0;
	char *name;

	while (ant < v->ins->nb_ants)
	{
		if (v->ants[ant] && v->ants[ant][CURRENT] != -1)
		{
			x = v->ins->room[v->ants[ant][CURRENT]].pos.x;
			y = v->ins->room[v->ants[ant][CURRENT]].pos.y;
			deltax = v->step * (v->ins->room[v->ants[ant][NEXT]].pos.x - x) / 50.0;
			deltay = v->step * (v->ins->room[v->ants[ant][NEXT]].pos.y - y) / 50.0;
			name = ft_itoa(ant + 1);
			mlx_string_put(v->mlx, v->win, x + deltax + 10, y + deltay - 15, COL_ANTNAME, name);
			ft_strdel(&name);
		}
		++ant;
	}

}


int		display_moves(VISU *v, int color, int option)
{
	int ant;

	ant = 0;
	(void)color;
	(void)option;
	if (!v->ins->nb_ants)
		return (-1);
	while (ant < v->ins->nb_ants)
	{
		if (v->ants[ant] && v->ants[ant][0] != -1 && v->ants[ant][0] != v->graphe->end)
			display_ant(v, v->ants[ant], 4);
		++ant;
	}
	return (0); 
}
	


int		main(void)
{
	static VISU	v;
	int		err;
	int		i;

	i = -1;
	set_env(&v);
	if ((err = read_instructions(&v, NULL, 0, 0)))
	{
//		free_env(&e);
		return (display(&v, get_errmsg(err)));
	}
	if ((err = apply_commands(&v)))
	{
//		free_env(&e);
		return (display(&v, get_errmsg(err)));
	}
	ft_init_win(&v);
	ft_get_img(&v);
//	ft_setextremes(&v);
//	change_val(&v);

	ft_transform_points((void *)&v);
	ft_points_to_img(&v);
	display_rooms(&v);
	mlx_put_image_to_window(v.mlx, v.win, v.img.img, 0, 0);
	v.map = (int *)ft_memalloc(sizeof(int) * v.win_h * v.win_w);
	v.ants = (int **)ft_memalloc(sizeof(int *) * (v.ins->nb_ants + 1));

	while (++i < v.ins->nb_ants)
	{
		if (!(v.ants[i] = (int *)ft_memalloc(sizeof(int) * 2)))
			return (ERR_ALLOC);
		v.ants[i][0] = -1;
		v.ants[i][1] = -1;
	}
	
	mlx_hook(v.win, KeyPress, KeyPressMask, ft_dealkey, (void *)&v);
	mlx_loop(v.mlx);

	return (0);
}
