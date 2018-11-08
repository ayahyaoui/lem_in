/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_scale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:52:20 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 17:43:16 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ft_getm_scaledown(VISU *v, double (*dest)[4][4])
{
	static int	iteration;
	double		ratio;

	if (!iteration || v->revert)
		v->mesh_size = 1;
	ft_44minit(dest, 1);
	ratio = 1.0 / v->mesh_size;
	(*dest)[0][0] = ratio;
	(*dest)[1][1] = ratio;
	(*dest)[2][2] = ratio;
	v->mesh_size = 1;
	++iteration;
}

void	ft_getm_scaleup(VISU *v, double (*dest)[4][4])
{
	ft_44minit(dest, 1);
	v->mesh_size = v->mesh_init;
	(*dest)[0][0] = v->mesh_size;
	(*dest)[1][1] = v->mesh_size;
	(*dest)[2][2] = v->mesh_size;
}

void	ft_getm_zoom(VISU *v, double (*dest)[4][4])
{
	ft_44minit(dest, 1);
	(*dest)[0][0] = v->uinput.zoom;
	(*dest)[1][1] = v->uinput.zoom;
	(*dest)[2][2] = v->uinput.zoom;
}
