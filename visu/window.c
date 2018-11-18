/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:52:54 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 16:15:05 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <stdlib.h>

static int	ft_launch_window(VISU *v)
{
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, v->win_w, v->win_h, WIN_TITLE);
	return (NO_ERR);
}

int			ft_close_window(VISU *v)
{
	mlx_clear_window(v->mlx, v->win);
	mlx_destroy_window(v->mlx, v->win);
	exit(0);
}

void	ft_get_meshsize(VISU *v)
{
	while ((v->width * v->mesh_init > (v->win_w - PADDING))
			|| (v->height * v->mesh_init > (v->win_h - PADDING)))
		--v->mesh_init;
}

int			ft_init_win(VISU *v)
{
//	ft_printf("init win| width = %d mesh_size = %d MIN W = %d SCREEN = %d\n", v->width, v->mesh_size, MIN_W, SCREEN_W);
	if ((v->win_w = v->width * v->mesh_size + MIN_W) > SCREEN_W)
		v->win_w = SCREEN_W;
	if ((v->win_h = v->height * v->mesh_size + MIN_H) > SCREEN_H)
		v->win_h = SCREEN_H;
	if (v->graphe->nb_rooms > SCREEN_W) // verifier pour tres grandes map
	{
		v->win_w = v->graphe->nb_rooms;
		v->win_h = v->graphe->nb_rooms;
	}
//	ft_printf("win w = %d win h = %d\n", v->win_w, v->win_h);
	if (v->win_h == SCREEN_H || v->win_w == SCREEN_W)
		ft_get_meshsize(v);

	ft_4vinit(&v->min, v->win_w, v->win_h, v->win_w * v->win_h);
	ft_4vinit(&v->max, 0, 0, 0);
//	ft_printf("minx = %d miny = %d\n", v->min.x, v->min.y);
	v->ppmove = v->win_h * v->win_w * PPMOVE_RATIO;
	if (!ft_launch_window(v))
		return (ERR_MLX);
	return (NO_ERR);
}
