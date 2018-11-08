/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:58:47 by emuckens          #+#    #+#             */
/*   Updated: 2018/11/08 16:12:58 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		main(void)
{
	static VISU	v;
	int		err;

	set_env(&v);
	if ((err = read_instructions(&v, NULL, 0, 0)))
	{
	//	free_env(&e);
		return (display(&v, get_errmsg(err)));
	}
	if ((err = apply_commands(&v)))
	{
	//	free_env(&e);
		return (display(&v, get_errmsg(err)));
	}
	ft_init_win(&v);
	ft_get_img(&v);
	ft_printf("after init img\n");
	mlx_hook(v.win, KeyPress, KeyPressMask, ft_dealkey, (void *)&v);
	ft_printf("after deal key\n");
//	ft_printf("nb rooms = %d\n", e.graphe->nb_rooms);
	mlx_expose_hook(v.win, &ft_transform_points, (void *)&v);
	mlx_loop(v.mlx);

	return (0);
}
