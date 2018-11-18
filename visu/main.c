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
	if (!v || !v->ins)
		return (-1);
	while (++ant < v->ins->nb_ants)
		v->ants[ant] = -1;
	ant = 0;
	while (ant <= v->ins->nb_ants)
	{
		if (!(antsplit = ft_strsplit(split[ant], '-')))
			return (ERR_READ);
		ft_printf("check split 0 = %s\n", antsplit[0]);
		num = ft_atoi(antsplit[0] + 1);
		v->ants[num - 1] = get_room_index(v, antsplit[1], ft_strlen(antsplit[1]));
		ft_printf("ant %d is in room index %d\n", num, v->ants[num - 1]); 
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
			mlx_string_put(v->mlx, v->win, v->ins->room[v->ants[ant]].pos.x + 10, v->ins->room[v->ants[ant]].pos.y - 10, COL_ANTNAME, name);
			ft_strdel(&name);
		}
		++ant;
	}
	mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->start].pos.x + 13, v->ins->room[v->graphe->start].pos.y - 5, 0x00FF00, "START");
	mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->end].pos.x + 13, v->ins->room[v->graphe->end].pos.y - 5, 0x00FF00, "END");

}


int		display_moves(VISU *v, int color, int option)
{
	int ant;

	ant = 0;
	if (!v->ants)
		return (-1);
//	ft_bzero(v->img.img, v->win_w);
//	ft_memmove(v->img.img, v->map, sizeof(v->map));
	while (ant < v->ins->nb_ants)
	{
	ft_printf("ant = %d, v->ants[ant] = %d\n", ant, v->ants[ant]);
		if (option && v->ants[ant] == -1)
			display_square(v, v->ants[ant], 4, color);
		else if (v->ants[ant] != -1)
		{
//			ft_points_to_img(v);
			display_square(v, v->ants[ant], 4, color);
			
		}

		++ant;

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
//	ft_printf("after init img\n");
	ft_transform_points((void *)&v);

	v.map = (int *)ft_memalloc(sizeof(int) * v.win_h * v.win_w);
//	unsigned int room = 0;
//	anim_moves(&v, NULL, 0 );
//	while (room < v.graphe->nb_rooms)
//{
//	ft_printf("room name = %s x = %d y = %d\n", v.ins->room[room].name, v.ins->room[room].pos.x, v.ins->room[room].pos.y);
//++room;
//	mlx_put_image_to_window(v.mlx, v.win, v.img.img, 0, 0);
//}//	mlx_string_put(v.mlx, v.win, v.ins->room[v.graphe->start].pos.x, v.ins->room[v.graphe->start].pos.y, 0x00FF00, "START");
//	mlx_string_put(v.mlx, v.win, v.ins->room[v.graphe->end].pos.x, v.ins->room[v.graphe->end].pos.y, 0x00FF00, "END");
//	ft_transform_points((void *)&v);

	v.ants = (int *)ft_memalloc(sizeof(int) * (v.ins->nb_ants + 1));
//	display_moves(&v, COL_ANT);

	mlx_hook(v.win, KeyPress, KeyPressMask, ft_dealkey, (void *)&v);
//	ft_printf("after deal key\n");
//	ft_printf("nb rooms = %d\n", e.graphe->nb_rooms);
//	mlx_expose_hook(v.win, &anim_moves, (void *)&v);
//	anim_moves(&v, NULL, 0);
	mlx_loop(v.mlx);

	return (0);
}
