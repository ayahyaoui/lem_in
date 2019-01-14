/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 13:59:11 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdio.h>


void		draw_ant_legs(VISU *v, int index, int scale, int option)
{
	int x;
	int y;

	x = v->ins->room[index].pos.x;
	y = v->ins->room[index].pos.y;
	v->coord.x0 = option ? x + scale : x - scale;
	v->coord.x0 -= 2;
	v->coord.y0 = y - scale;
	v->coord.x1 = option ? x - scale : x + scale;
	v->coord.x1 -= 2;
	v->coord.y1 = y + scale;
	ft_drawline(v);
}

void		display_ant(VISU *v, int index, int scale)
{
	int x;
	int y;

	x = v->ins->room[index].pos.x;
	y = v->ins->room[index].pos.y;
	if (scale < 5)
		scale = 5;
	v->color = COL_ANT;
	display_square(v, index, -2, COL_ANT);
	v->coord.x0 = x - 2 * scale + 2;
	v->coord.y0 = y;
	v->coord.x1 = x + 4;
	v->coord.y1 = y;
	ft_drawline(v);
	v->coord.x0 = x - 2;
	v->coord.y0 = y - scale;
	v->coord.x1 = x - 2;
	v->coord.y1 = y + scale;
	ft_drawline(v);
	draw_ant_legs(v, index, scale, 0);
	draw_ant_legs(v, index, scale, 1);
}

void		display_square(VISU *v, int index, int width, int color)
{
	int col;
	int row;
	double x;
	double y;

	x = v->ins->room[index].pos.x;
	y = v->ins->room[index].pos.y;
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

int		read_moves(VISU *v, char *line)
{
	char **split;
	char **antsplit;
	int ant;
	int num;

	if (!(split = ft_strsplit(line, ' ')))
		return (ERR_READ);
	ant = -1;
	if (!v || !v->ins)
		return (-1);
	while (++ant < v->ins->nb_ants)
		v->ants[ant] = -1;
	ant = 0;
	while (ant <= v->ins->nb_ants)
	{
		if (!(antsplit = ft_strsplit(split[ant], '-')))
			return (ERR_READ);
		num = ft_atoi(antsplit[0] + 1);
		v->ants[num - 1] = get_room_index(v, antsplit[1], ft_strlen(antsplit[1]));
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

	ant = 0;
	char *name;

	while (ant < v->ins->nb_ants)
	{
		if (v->ants[ant] != -1)
		{
			name = ft_itoa(ant + 1);
			ft_printf("name = %s\n", name);
			mlx_string_put(v->mlx, v->win, v->ins->room[v->ants[ant]].pos.x + 10, v->ins->room[v->ants[ant]].pos.y - 15, COL_ANTNAME, name);
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
	if (!v->ants)
		return (-1);
	while (ant < v->ins->nb_ants)
	{
		if (v->ants[ant] != -1)
			display_ant(v, v->ants[ant], 4);
		++ant;
	}
	return (0); 
}
	


int		main(void)
{
	static VISU	v;
	int		err;

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
	v.ants = (int *)ft_memalloc(sizeof(int) * (v.ins->nb_ants + 1));
	mlx_hook(v.win, KeyPress, KeyPressMask, ft_dealkey, (void *)&v);
//	mlx_expose_hook(v.win, &anim_moves, (void *)&v);
//	anim_moves(&v, NULL, 0);
	mlx_loop(v.mlx);

	return (0);
}
