/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_44maddrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 17:21:25 by emuckens          #+#    #+#             */
/*   Updated: 2018/05/20 17:25:00 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_44maddrows(double (*m)[4][4], int row_dest, int row_add)
{
	int col;

	col = 0;
	while (col < 4)
	{
		(*m)[row_dest][col] += (*m)[row_add][col];
		++col;
	}
}
