/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:48:36 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 18:29:44 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <math.h>

static void		ft_input_rot_and_height(VISU *v, int key)
{
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
	ft_printf("before move hor = %d move ver = %d\n", v->uinput.mv_hor, v->uinput.mv_ver);
	if (key == KEY_LF)
		v->uinput.mv_hor -= v->ppmove;
	else if (key == KEY_RT)
		v->uinput.mv_hor += v->ppmove;
	else if (key == KEY_UP)
		v->uinput.mv_ver -= v->ppmove;
	else if (key == KEY_DW)
		v->uinput.mv_ver += v->ppmove;
	else if (key == KEY_INVERT)
		v->uinput.invert *= -1;
	else if (key == KEY_ZMIN && v->maxzoomin < 5)
	{
		++v->maxzoomin;
		--v->maxzoomout;
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
	return (key == 1
//			|| key == KEY_XUP
//			|| key == KEY_XDW
//			|| key == KEY_YUP
//			|| key == KEY_YDW
//			|| key == KEY_LF
//			|| key == KEY_RT
//			|| key == KEY_UP
//			|| key == KEY_DW
			|| key == KEY_ZMIN
			|| key == KEY_ZMOUT
			|| key == KEY_INVERT
			|| key == KEY_DEFAULT);
}

int				ft_dealkey(int key, void *param)
{
	mlx_clear_window(((VISU *)param)->mlx, ((VISU *)param)->win);
	ft_bzero(((VISU *)param)->img.ptr,
			((VISU *)param)->win_w * ((VISU *)param)->win_h * 4);
	((VISU *)param)->uinput.rotx = 0;
	((VISU *)param)->uinput.roty = 0;
	((VISU *)param)->uinput.zoom = 1.0;
	((VISU *)param)->setextremes = 0;
	if (ft_isvalid_key(key))
	{
		ft_input_rot_and_height((VISU *)param, key);
		ft_input_move((VISU *)param, key);
//		ft_input_color((VISU *)param, key);
//		if (key == KEY_DEFAULT)
//			((VISU *)param)->revert = 1;
		return (ft_transform_points((VISU *)param));
	}
	else if (key == KEY_ESC)
		return (ft_close_window((VISU *)param));
	ft_points_to_img(((VISU *)param));
//	display menu
	mlx_put_image_to_window(((VISU *)param)->mlx, ((VISU *)param)->win,
			((VISU *)param)->img.img, 0, 0);
//	ft_menu_txt((VISU *)param);
	return (0);
}
