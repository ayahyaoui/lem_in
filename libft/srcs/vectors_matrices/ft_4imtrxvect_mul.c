/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4imtrxvect_mul.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:18:42 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 16:35:14 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_4ivect		ft_4imtrxvect_mul(double (*m)[4][4], t_4ivect *ver)
{
	t_4ivect result;

	ft_4ivinit(&result, 0, 0, 0);
	result.x = (*m)[0][0] * (*ver).x + (*m)[0][1] * (*ver).y
		+ (*m)[0][2] * (*ver).z + (*m)[0][3] * (*ver).w;
	result.y = (*m)[1][0] * (*ver).x + (*m)[1][1] * (*ver).y
		+ (*m)[1][2] * (*ver).z + (*m)[1][3] * (*ver).w;
	result.z = (*m)[2][0] * (*ver).x + (*m)[2][1] * (*ver).y
		+ (*m)[2][2] * (*ver).z + (*m)[2][3];
	return (result);
}
