/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:48:36 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/19 20:50:55 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "stdio.h"
#include <math.h>

static void		ft_input_rot_and_height(VISU *v, int key)
{
	v->uinput.rotx = 0;
	v->uinput.roty = 0;
	if (key == KEY_XUP)
		v->uinput.rotx = M_PI / 24.0;
	else if (key == KEY_XDW)
		v->uinput.rotx = -M_PI / 24.0;
	else if (key == KEY_YUP)
		v->uinput.roty = -M_PI / 24.0;
	else if (key == KEY_YDW)
		v->uinput.roty = M_PI / 24.0;
}


static void		ft_input_move(VISU *v, int key)
{
	v->uinput.zoom = 1;
	ft_printf("before move hor = %d move ver = %d\n", v->uinput.mv_hor, v->uinput.mv_ver);
	if (key == KEY_LF)
		v->uinput.mv_hor -= v->ppmove;
	else if (key == KEY_RT)
		v->uinput.mv_hor += v->ppmove;
	else if (key == KEY_UP)
		v->uinput.mv_ver -= v->ppmove;
	else if (key == KEY_DW)
		v->uinput.mv_ver += v->ppmove;
//	else if (key == KEY_INVERT)
//		v->uinput.invert *= -1;
	else if (key == KEY_ZMIN && v->maxzoomin < 5)
	{
		++v->maxzoomin;
		--v->maxzoomout;
		ft_printf("ZOOMIN!!!\n");
		v->uinput.zoom = 2.0;
	}
	else if (key == KEY_ZMOUT && v->maxzoomout < 5)
	{
		++v->maxzoomout;
		--v->maxzoomin;
		v->uinput.zoom = 0.5;
	}
	
	ft_printf("after move hor = %d move ver = %d\n", v->uinput.mv_hor, v->uinput.mv_ver);
}

static int		ft_isvalid_key(int key)
{
	return (/*key == 1*/
			 key == KEY_XUP
			|| key == KEY_XDW
			|| key == KEY_YUP
			|| key == KEY_YDW
			|| key == KEY_LF
			|| key == KEY_RT
			|| key == KEY_UP
			|| key == KEY_DW
			|| key == KEY_ZMIN
			|| key == KEY_ZMOUT
/*			|| key == KEY_DEFAULT*/);
}

int				ft_dealkey(int key, VISU *v)
{

	ft_printf("key = %d\n", key);
	ft_bzero(v->img.ptr, v->win_w * v->win_h * sizeof(int));
	if (ft_isvalid_key(key))
	{
		ft_input_rot_and_height(v, key);
		ft_input_move(v, key);
		ft_printf("valid key, transform points\n");
		ft_transform_points(v);
	}

	else if (key == KEY_ESC)
		return (ft_close_window(v));
	else if (key == KEY_PAUSE && !v->pause)
		v->pause = 1;
	else if (key == KEY_PAUSE)
	{
		mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
		v->pause = 0;
	}
	ft_points_to_img(v);
	display_rooms(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
	mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->start].pos.x + 13, v->ins->room[v->graphe->start].pos.y - 10, COL_TUBES, "START");
	mlx_string_put(v->mlx, v->win, v->ins->room[v->graphe->end].pos.x + 13, v->ins->room[v->graphe->end].pos.y - 10, COL_TUBES, "END");

	mlx_loop_hook(v->mlx, anim_moves, v);
	return (0);
}
