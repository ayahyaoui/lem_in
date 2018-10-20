/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dsqrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 17:30:54 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:14:25 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_dsqrt(double num)
{
	double root;

	root = 0;
	while (root * root < num)
		root += 0.1;
	if (root * root - num > 0.001)
	{
		root -= 0.1;
		while (root * root < num)
			root += 0.0001;
	}
	return (root);
}
