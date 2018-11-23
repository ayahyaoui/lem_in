/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_rot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:56:30 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/19 20:50:53 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include <math.h>

void	ft_getm_rot(VISU *v, double (*dest)[4][4])
{
	double angle[8];

	ft_44minit(dest, 1);
	angle[COSX] = cos(v->uinput.rotx);
	angle[SINX] = sin(v->uinput.rotx);
	angle[COSY] = cos(v->uinput.roty);
	angle[SINY] = sin(v->uinput.roty);
	(*dest)[0][0] = angle[COSY];
	(*dest)[0][2] = angle[SINY];
	(*dest)[1][0] = -angle[SINY] * angle[SINX];
	(*dest)[1][1] = angle[COSX];
	(*dest)[1][2] = -angle[COSY] * angle[SINX];
	(*dest)[2][0] = -angle[SINY] * angle[COSX];
	(*dest)[2][1] = angle[SINX];
	(*dest)[2][2] = angle[COSY] * angle[COSX];
}
