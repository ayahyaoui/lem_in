/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/16 21:21:19 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdio.h>



void		display_square(VISU *v, int index, int width, int color)
{
	int col;
	int row;
	double x;
	double y;

	x = v->ins->room[index].pos.x;
	y = v->ins->room[index].pos.y;

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
	while (++ant < v->ins->nb_ants)
		v->ants[ant] = -1;
	ant = -1;
	while (++ant < v->ins->nb_ants)
	{
		if (!(antsplit = ft_strsplit(split[ant], '-')))
			return (ERR_READ);
		num = ft_atoi(antsplit[0] + 1);
		v->ants[num] = get_room_index(v, antsplit[1], ft_strlen(antsplit[1]));
		ft_strdel(&antsplit[0]);
		ft_strdel(&antsplit[1]);
		ft_memdel((void **)&antsplit);
		ft_strdel(&split[ant]);
//		ft_printf("ant %d is in room %s\n", num, v->ins->room[v->ants[num]]); 
	}
	ft_memdel((void **)&split);
	return (0);
}


void		display_ant_names(VISU *v)
{
	int ant;

	ant = -1;
	char *name;

	while (++ant < v->ins->nb_ants)
	{
		if (v->ants[ant] != -1)
		{
			name = ft_itoa(ant + 1);
			mlx_string_put(v->mlx, v->win, v->ins->room[v->ants[ant]].pos.x, v->ins->room[v->ants[ant]].pos.y, 0xFFFFFF, name);
			ft_strdel(&name);
		}
	}
	mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->start].pos.x, v->ins->room[v->graphe->start].pos.y, 0x00FF00, "START");
	mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->end].pos.x, v->ins->room[v->graphe->end].pos.y, 0x00FF00, "END");

}


int		display_moves(VISU *v)
{
	int ant;

	ant = -1;
//	ft_bzero(v->img.img, v->win_w);
//	ft_memmove(v->img.img, v->map, sizeof(v->map));
	while (++ant < v->ins->nb_ants)
	{
		ft_printf("ant = %d, v->ants[ant] = %d\n", ant, v->ants[ant]);
		if (v->ants[ant] != -1)
		{
			ft_points_to_img(v);
			display_square(v, v->ants[ant], 4, 0x00FF00);
			
		}

	}
//	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
//	display_ant_names(v);

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
	ft_printf("after init img\n");
	ft_transform_points((void *)&v);

	v.map = (int *)ft_memalloc(sizeof(int) * v.win_h * v.win_w);
	unsigned int room = 0;
	while (room < v.graphe->nb_rooms)
{
	ft_printf("room name = %s x = %d y = %d\n", v.ins->room[room].name, v.ins->room[room].pos.x, v.ins->room[room].pos.y);
++room;
	mlx_put_image_to_window(v.mlx, v.win, v.img.img, 0, 0);
}	mlx_string_put(v.mlx, v.win, v.ins->room[v.graphe->start].pos.x, v.ins->room[v.graphe->start].pos.y, 0x00FF00, "START");
	mlx_string_put(v.mlx, v.win, v.ins->room[v.graphe->end].pos.x, v.ins->room[v.graphe->end].pos.y, 0x00FF00, "END");

//	mlx_hook(v.win, KeyPress, KeyPressMask, ft_dealkey, (void *)&v);
	ft_printf("after deal key\n");
//	ft_printf("nb rooms = %d\n", e.graphe->nb_rooms);
//	mlx_expose_hook(v.win, &ft_transform_points, (void *)&v);
//	anim_moves(&v, NULL, 0);
	mlx_loop(v.mlx);

	return (0);
}
