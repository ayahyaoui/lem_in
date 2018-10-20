/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_4vectvect_mul.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 15:14:57 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:17:42 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_4vectvect_mul(t_4vect hor, t_4vect ver)
{
	double result;

	result = 0;
	result += hor.x * ver.x + hor.y * ver.y + hor.z * ver.z + hor.w * ver.w;
	return (result);
}
